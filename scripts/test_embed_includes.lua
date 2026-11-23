local root = vim.fn.getcwd()
local directory = vim.fn.tempname()
vim.fn.mkdir(directory, "p")
local source = directory .. "/solution.hpp"
vim.fn.writefile({ "BasedOnStyle: LLVM", "IndentWidth: 7", "AllowShortFunctionsOnASingleLine: None" }, directory .. "/.clang-format")
vim.fn.writefile({ "#pragma once", "struct Item {};" }, directory .. "/item.hpp")
vim.fn.writefile({ '#include "item.hpp"', "#define VALUE 42", "", "int answer(){", "return VALUE;", "}" }, source)

local copied = {}
vim.g.clipboard = {
    name = "test",
    copy = { ["+"] = function(lines) copied = lines end, ["*"] = function() end },
    paste = { ["+"] = function() return { copied, "V" } end, ["*"] = function() return { {}, "V" } end },
    cache_enabled = 0,
}
vim.o.clipboard = "unnamedplus"
local messages = {}
vim.notify = function(message, level) table.insert(messages, { message, level }) end

dofile(root .. "/.nvim.lua")
vim.cmd.edit(vim.fn.fnameescape(source))
local real_system = vim.system
vim.system = function(command, options, callback)
    if command[1] == "uv" then
        local args = { root .. "/.venv/bin/python" }
        vim.list_extend(args, vim.list_slice(command, 5))
        command = args
    end
    return real_system(command, options, callback)
end

vim.cmd.EmbedIncludes("--verbose")
assert(vim.wait(15000, function() return #copied > 0 or #messages > 1 end, 10), "embedding timed out")
assert(#copied > 0, vim.inspect(messages))
local formatted = table.concat(copied, "\n")
assert(formatted:find("struct Item {};", 1, true))
assert(formatted:find("\n\n", 1, true), "blank lines were lost")
assert(formatted:find("       return VALUE;", 1, true), "source formatting rules were not used")
assert(formatted:find("#define VALUE 42", 1, true))
assert(vim.fn.getregtype('"') == "V")
local register_lines = vim.deepcopy(copied)
if register_lines[#register_lines] == "" then table.remove(register_lines) end
assert(vim.deep_equal(vim.fn.getreg('"', 1, true), register_lines))
assert(vim.fn.glob(directory .. "/*_mono.*") == "")
assert(#messages == 1 and messages[1][1]:find("item.hpp: embed", 1, true))

copied = {}
messages = {}
vim.cmd.EmbedIncludesPreprocess()
assert(vim.wait(15000, function() return #copied > 0 or #messages > 0 end, 10), "preprocessing timed out")
formatted = table.concat(copied, "\n")
assert(formatted:find("       return 42;", 1, true), vim.inspect(messages))
assert(not formatted:find("#define", 1, true))

for _, fail_at in ipairs({ 1, 2 }) do
    local calls = 0
    messages = {}
    local before = vim.deepcopy(copied)
    vim.system = function(_, _, callback)
        calls = calls + 1
        if calls == fail_at then
            callback({ code = 1, stdout = "", stderr = "deliberate failure" })
        else
            callback({ code = 0, stdout = "int answer = 42;\n", stderr = "" })
        end
    end
    vim.cmd.EmbedIncludes()
    assert(vim.wait(1000, function() return #messages > 0 end, 10))
    assert(messages[1][2] == vim.log.levels.ERROR)
    assert(messages[1][1]:find("deliberate failure", 1, true))
    assert(vim.deep_equal(before, copied), "failure replaced the register")
    assert(calls == fail_at)
end

vim.fn.delete(directory, "rf")
print("EmbedIncludes: formatting, registers, diagnostics, and failure paths passed")

vim.api.nvim_create_autocmd('LspAttach', {
    group = vim.api.nvim_create_augroup('my.lsp', {}),
    callback = function(args)
        local client = assert(vim.lsp.get_client_by_id(args.data.client_id))
        -- Auto-format ("lint") on save.
        -- Usually not needed if server supports "textDocument/willSaveWaitUntil".
        if not client:supports_method('textDocument/willSaveWaitUntil')
            and client:supports_method('textDocument/formatting') then
            vim.api.nvim_create_autocmd('BufWritePre', {
                group = vim.api.nvim_create_augroup('my.lsp', { clear = false }),
                buffer = args.buf,
                callback = function()
                    vim.lsp.buf.format({ bufnr = args.buf, id = client.id, timeout_ms = 1000 })
                end,
            })
        end
    end,
})


-- Workspace root (current working directory)
local root = vim.loop.cwd()

-- Absolute path to script
local automation_script_path = root .. "/" .. "scripts/automation.py"

vim.api.nvim_create_user_command("EmbedIncludes", function(opts)
    local verbose = false

    for _, arg in ipairs(opts.fargs) do
        if arg == "--verbose" or arg == "-v" then
            verbose = true
        end
    end

    -- Save current buffer
    vim.cmd("write")

    -- Absolute path to current file
    local file_path = vim.fn.expand("%:p")
    if file_path == "" then
        vim.notify("No file is currently open", vim.log.levels.ERROR)
        return
    end

    -- The command
    local cmd = { automation_script_path, 'embed_includes', file_path }

    local stdout_lines = {}

    -- Execute
    vim.fn.jobstart(cmd, {

        on_stdout = function(_, data)
            if not data then return end
            for _, line in ipairs(data) do
                if line ~= "" then
                    table.insert(stdout_lines, line)
                end
            end
        end,

        on_stderr = function(_, data)
            if data and #data > 0 then
                vim.notify(table.concat(data, "\n"), vim.log.levels.ERROR)
            end
        end,

        on_exit = function(_, code)
            if verbose then
                if #stdout_lines > 0 then
                    vim.notify(table.concat(stdout_lines, "\n"))
                end
            end

            if code ~= 0 then
                vim.notify("EmbedIncludes failed", vim.log.levels.ERROR)
                return
            end

            -- Build mono file path: suffix before extension
            local dir       = vim.fn.fnamemodify(file_path, ":h")
            local base      = vim.fn.fnamemodify(file_path, ":t:r")
            local ext       = vim.fn.fnamemodify(file_path, ":e")
            local mono_file = string.format("%s/%s_mono.%s", dir, base, ext)

            if vim.fn.filereadable(mono_file) == 0 then
                vim.notify("Mono file not found: " .. mono_file, vim.log.levels.ERROR)
                return
            end

            -- Read and yank
            local lines = vim.fn.readfile(mono_file)
            vim.schedule(function()
                vim.fn.setreg('"', lines, 'l')
                local clipboard = vim.o.clipboard or ""
                if clipboard:match("unnamedplus") then
                    vim.fn.setreg("+", lines, 'l')
                end
            end)
        end,
    })
end, {
    nargs = "*",
    complete = function()
        return { "--verbose", "-v" }
    end,
})


local function normalize_name(name)
    name = name:gsub("[^0-9a-zA-Z%s]", "")
    name = name:gsub("%s+", "_")
    return name
end


vim.api.nvim_create_user_command("CreateSolution", function(opts)
    -- Normalize project name
    local name = normalize_name(table.concat(opts.fargs, " "))

    -- Path to created header
    local header_path = root .. "/code/" .. name .. "/" .. name .. ".hpp"

    -- The command
    local cmd = { automation_script_path, 'create', '--name', name }

    -- Execute
    vim.fn.jobstart(cmd, {
        stdout_buffered = true,
        stderr_buffered = true,

        on_stdout = function(_, data)
            if data and #data > 0 then
                vim.notify(table.concat(data, "\n"))
            end
        end,

        on_stderr = function(_, data)
            if data and #data > 0 then
                vim.notify(table.concat(data, "\n"), vim.log.levels.ERROR)
            end
        end,

        on_exit = function(_, code)
            if code == 0 then
                -- Open the created file on the main thread
                vim.schedule(function()
                    vim.cmd("edit " .. vim.fn.fnameescape(header_path))
                end)
            else
                vim.notify("CreateSolution failed", vim.log.levels.ERROR)
            end
        end,
    })
end, {
    nargs = 1
})

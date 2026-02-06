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


vim.api.nvim_create_user_command("EmbedIncludes", function()
    -- Save current buffer
    vim.cmd("write")

    -- Absolute path to current file
    local file_path = vim.fn.expand("%:p")
    if file_path == "" then
        vim.notify("No file is currently open", vim.log.levels.ERROR)
        return
    end


    -- Absolute path to script
    local script_path = root .. "/" .. "scripts/embed_includes.py"

    -- Build command
    local cmd = { script_path, file_path }

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
    })
end, {})


local function normalize_name(name)
    name = name:gsub("[^0-9a-zA-Z%s]", "")
    name = name:gsub("%s+", "_")
    return name
end


vim.api.nvim_create_user_command("CreateSolution", function(opts)
    -- Absolute path to script
    local script_path = root .. "/" .. "scripts/automation.py"

    -- Normalize project name
    local name = normalize_name(table.concat(opts.fargs, " "))

    -- The command
    local cmd = { script_path, 'create', '--name', name }

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
    })
end, {
    nargs = 1
})

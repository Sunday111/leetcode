vim.api.nvim_create_autocmd('LspAttach', {
  group = vim.api.nvim_create_augroup('my.lsp', {}),
  callback = function(args)
    local client = assert(vim.lsp.get_client_by_id(args.data.client_id))
    if client:supports_method('textDocument/implementation') then
      -- Create a keymap for vim.lsp.buf.implementation ...
    end
    -- Auto-format ("lint") on save.
    -- Usually not needed if server supports "textDocument/willSaveWaitUntil".
    if not client:supports_method('textDocument/willSaveWaitUntil')
        and client:supports_method('textDocument/formatting') then
      vim.api.nvim_create_autocmd('BufWritePre', {
        group = vim.api.nvim_create_augroup('my.lsp', {clear=false}),
        buffer = args.buf,
        callback = function()
          vim.lsp.buf.format({ bufnr = args.buf, id = client.id, timeout_ms = 1000 })
        end,
      })
    end
  end,
})

-- Script path relative to workspace root
local script_rel_path = "scripts/embed_includes.py"

vim.api.nvim_create_user_command("EmbedIncludes", function()
  -- Save current buffer
  vim.cmd("write")

  -- Absolute path to current file
  local file_path = vim.fn.expand("%:p")
  if file_path == "" then
    vim.notify("No file is currently open", vim.log.levels.ERROR)
    return
  end

  -- Workspace root (current working directory)
  local root = vim.loop.cwd()

  -- Absolute path to script
  local script_path = root .. "/" .. script_rel_path

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


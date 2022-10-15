require('nvim-tree').setup {
    diagnostics = {
        enable = true,
        },
    filters = {
        dotfiles = true,
    },
     view = {
        adaptive_size = true,
        mappings = {
          list = {
            { key = "u", action = "dir_up" },
          },
        },
      },
}

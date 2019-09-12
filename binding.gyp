{
  "targets": [
    {
      "target_name": "roll",
      "include_dirs": [
        "include"
      ],
      "link_settings": {
        "conditions": [
          ["OS=='linux'", {
            "libraries": [
              "<(module_root_dir)/build/lib/openrpg/libroll-parser.so"
            ]
          }],
          ["OS=='win'", {
            "libraries": [
              "<(module_root_dir)/build/lib/Debug/roll-parser"
            ]
          }]
        ],
      },
      "sources": [ 
        "wrappers/roll/rollAddon.cpp",
        "wrappers/roll/rollWrapper.cpp"
      ]
    }
  ]
}
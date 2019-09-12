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
              "<(module_root_dir)/build/lib/roll-parser"
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
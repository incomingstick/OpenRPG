{
  "targets": [
    # {
    #   'target_name': 'prebuild',
    #   'type': 'none',
    #   'actions': [
    #     {
    #       'action_name': 'build_core',
    #       'message': 'Building ORPG Core...',
    #       'inputs': [''],
    #       'outputs': [''],
    #       "action": [
    #         "cd <(module_root_dir) && node build.js && cd build/"
    #       ]
    #     },
    #   ],
    # },
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
              "<(module_root_dir)/build/lib/Release/roll-parser.lib",
              "<(module_root_dir)/build/lib/Release/roll-parser.exp"
            ]
          }]
        ],
      },
      "sources": [ 
        "<(module_root_dir)/wrappers/roll/rollAddon.cpp",
        "<(module_root_dir)/wrappers/roll/rollWrapper.cpp"
      ]
    }
  ]
}
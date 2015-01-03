{
  'target_defaults': {
    'conditions': [
      ['OS == "win"', {
        'msvs_settings': {
          'VCCLCompilerTool': {
            'AdditionalOptions': [ '/TP' ],
          }
        },
        'defines': [
          '_WIN32',
          'WIN32',
          '_CRT_NONSTDC_NO_DEPRECATE',
          '_DEBUG',
          '_WINDOWS',
          '_USRDLL',
          'JANSSON_DLL_EXPORTS',
          '_WINDLL',
          '_UNICODE',
          'UNICODE'
        ],
        'link_settings': {
          'libraries': [
            '-ladvapi32.lib',
            '-liphlpapi.lib',
            '-lpsapi.lib',
            '-lshell32.lib',
            '-lws2_32.lib'
          ],
        },
      }],   # OS == "win"
      ['OS != "win" ',{
        'defines':[
          '_LARGEFILE_SOURCE',
          '_FILE_OFFSET_BITS=64',
          '_GNU_SOURCE',
        ]
      }],   # OS != "win"
      ['TO == "ios"', {
        'xcode_settings': {
          'TARGETED_DEVICE_FAMILY': '1,2',
          'CODE_SIGN_IDENTITY': 'iPhone Developer',
          'IPHONEOS_DEPLOYMENT_TARGET': '5.0',
          'ARCHS': '$(ARCHS_STANDARD_32_64_BIT)',
        },
      }], # TO == "ios"
    ],    # conditions
  },

  'targets': [
    {
      'target_name': 'libpomelo',
      'type': '<(library)',
      'dependencies': [
        'deps/uv/uv.gyp:libuv',
        'deps/jansson/jansson.gyp:jansson',
      ],
      'include_dirs': [
        './include',
        './deps/uv/include',
        './deps/jansson/src',
      ],
      'sources': [
        'include/pomelo-private/common.h',
        'include/pomelo-private/internal.h',
        'include/pomelo-private/listener.h',
        'include/pomelo-private/map.h',
        'include/pomelo-private/ngx-queue.h',
        'include/pomelo-private/transport.h',
        'include/pomelo-private/jansson-memory.h',
        'include/pomelo-protobuf/pb-util.h',
        'include/pomelo-protobuf/pb.h',
        'include/pomelo-protocol/message.h',
        'include/pomelo-protocol/package.h',
        'include/pomelo.h',
        'src/client.c',
        'src/common.c',
        'src/listener.c',
        'src/map.c',
        'src/message.c',
        'src/msg-json.c',
        'src/msg-pb.c',
        'src/network.c',
        'src/package.c',
        'src/pb-decode.c',
        'src/pb-encode.c',
        'src/pb-util.c',
        'src/pkg-handshake.c',
        'src/pkg-heartbeat.c',
        'src/transport.c',
        'src/protocol.c',
        'src/thread.c',
        'src/jansson-memory.c',
      ],
      'conditions': [
        ['OS != "win"', {
          'cflags': [
            '-ggdb',
          ]
        }],
      ['library=="shared_library"', {
        'defines': ['BUILDING_PC_SHARED=1'], }],  # OS != "win"
      ],    # conditions
    },
  ],    # targets

  'conditions': [
    ['TO == "ios"',
      {
        'xcode_settings': {
          'SDKROOT': 'iphoneos',
        }, # xcode_settings
      },
    ],  # TO == "ios"
    ['TO == "pc"',
      {
        'targets': [
          {
            'target_name': 'destroy',
            'type': 'executable',
            'dependencies': [
              'libpomelo',
            ],
            'include_dirs': [
              'include/',
              './deps/uv/include',
              './deps/jansson/src',
            ],
            'sources': [
              'example/destroy.c'
            ],
          },
          {
            'target_name': 'notify',
            'type': 'executable',
            'dependencies': [
              'libpomelo',
            ],
            'include_dirs': [
              'include/',
              './deps/uv/include',
              './deps/jansson/src',
            ],
            'sources': [
              'example/notify.c'
            ],
          },
          {
            'target_name': 'request',
            'type': 'executable',
            'dependencies': [
              'libpomelo',
            ],
            'include_dirs': [
              'include/',
              './deps/uv/include',
              './deps/jansson/src',
            ],
            'sources': [
              'example/request.c'
            ],
          },
          {
            'target_name': 'echo',
            'type': 'executable',
            'dependencies': [
              'libpomelo',
            ],
            'include_dirs': [
              'include/',
              './deps/uv/include',
              './deps/jansson/src',
            ],
            'sources': [
              'example/echo.c'
            ],
          },
		      {
            'target_name': 'echo2',
            'type': 'executable',
            'dependencies': [
              'libpomelo',
            ],
            'include_dirs': [
              'include/',
              './deps/uv/include',
              './deps/jansson/src',
            ],
            'sources': [
              'example/echo2.c'
            ],
          },
          {
            'target_name': 'test_protobuf',
            'type': 'executable',
            'dependencies': [
              'libpomelo',
            ],
            'include_dirs': [
              'include/',
              './deps/uv/include',
              './deps/jansson/src',
            ],
            'sources': [
              'test/protobuf/test_protobuf.c',
              'src/pb-decode.c',
              'src/pb-encode.c',
              'src/pb-util.c'
            ],
          },
          {
            'target_name': 'robot_chat',
            'type': 'executable',
            'dependencies': [
              'libpomelo',
            ],
            'include_dirs': [
              'include/',
              './deps/uv/include',
              './deps/jansson/src',
            ],
            'sources': [
              'test/robot/robot_chat.c',
              'src/client.c',
              'src/network.c',
              'src/pkg-handshake.c'
            ],
           'cflags': [
             '-ggdb',
           ]
          },
        ]
      }
    ]   # TO == pc
  ],  # conditions
}

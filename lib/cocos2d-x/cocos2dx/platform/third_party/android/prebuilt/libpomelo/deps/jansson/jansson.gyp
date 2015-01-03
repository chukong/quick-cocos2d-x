{
  'conditions': [
    ['TO == "ios"', {
      'xcode_settings': {
        'SDKROOT': 'iphoneos',
      }, # xcode_settings
    }],  # TO == "ios"
  ],  # conditions

  'target_defaults': {
    'conditions': [
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
      'target_name': 'jansson',
      'type': '<(library)',
      'include_dirs': [
        './src'
      ],
      'sources': [
        'src/dump.c',
        'src/error.c',
        'src/hashtable.c',
        'src/hashtable.h',
        'src/jansson_private.h',
        'src/load.c',
        'src/memory.c',
        'src/pack_unpack.c',
        'src/strbuffer.c',
        'src/strbuffer.h',
        'src/strconv.c',
        'src/utf.c',
        'src/utf.h',
        'src/value.c',
        'src/jansson.h',
        'src/jansson_config.h'
      ],
      'conditions': [
        ['OS == "win"', {
          'defines': [
            'WIN32',
            '_CRT_NONSTDC_NO_DEPRECATE',
            '_DEBUG',
            '_WINDOWS',
            '_USRDLL',
            'JANSSON_DLL_EXPORTS',
            '_WINDLL',
            '_UNICODE',
            'UNICODE'
          ]
        }, {
          'cflags': [
              '-ggdb',
          ]
        }],   # OS == "win"
      ['OS == "win" and library == "shared_library"', {
        'sources' : [
          'src/jansson.def',
        ]
      }],
        ['OS=="ios"', {
          'xcode_settings': {
            'TARGETED_DEVICE_FAMILY': '1,2',
            'CODE_SIGN_IDENTITY': 'iPhone Developer',
            'IPHONEOS_DEPLOYMENT_TARGET': '5.0',
            'ARCHS': '$(ARCHS_STANDARD_32_64_BIT)',
          }, # xcode_settings
        }],  # OS=="ios"
        ['OS != "win"',{
          'ldflags': [
            '-no-undefined',
            '-export-symbols-regex \'^json_\'',
            '-version-info 8:0:4',
          ]
        }],   # OS != "win"
      ],    # conditions
    },
  ],
}

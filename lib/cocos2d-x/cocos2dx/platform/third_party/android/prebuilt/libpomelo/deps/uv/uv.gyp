{
  'variables': {
    'uv_use_dtrace%': 'false',
    # uv_parent_path is the relative path to libuv in the parent project
    # this is only relevant when dtrace is enabled and libuv is a child project
    # as it's necessary to correctly locate the object files for post
    # processing.
    'uv_parent_path': '',
    'uv_library%': 'static_library',
  },

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
      ['OS != "win"', {
        'defines': [
          '_LARGEFILE_SOURCE',
          '_FILE_OFFSET_BITS=64',
          '_GNU_SOURCE',
        ],
        'conditions': [
          ['OS=="solaris"', {
            'cflags': [ '-pthreads' ],
          }, {
            'cflags': [ '-pthread' ],
          }],
        ],
      }],
    ],
  },

  'targets': [
    {
      'target_name': 'libuv',
      'type': '<(uv_library)',
      'include_dirs': [
        'include',
        'include/uv-private',
        'src/',
      ],
      'direct_dependent_settings': {
        'include_dirs': [ 'include' ],
        'conditions': [
          ['OS != "win"', {
            'defines': [
              '_LARGEFILE_SOURCE',
              '_FILE_OFFSET_BITS=64',
            ],
          }],
          ['OS == "mac"', {
            'defines': [ '_DARWIN_USE_64_BIT_INODE=1' ],
          }],
          ['OS == "linux"', {
            'defines': [ '_POSIX_C_SOURCE=200112' ],
          }],
        ],
      },
      'defines': [
        'HAVE_CONFIG_H'
      ],
      'sources': [
        'common.gypi',
        'include/uv.h',
        'include/uv-private/ngx-queue.h',
        'include/uv-private/tree.h',
        'src/fs-poll.c',
        'src/inet.c',
        'src/uv-common.c',
        'src/uv-common.h',
        'src/version.c'
      ],
      'conditions': [
        [ 'OS=="win"', {
          'defines': [
            '_WIN32_WINNT=0x0600',
            '_GNU_SOURCE',
          ],
          'sources': [
            'include/uv-private/uv-win.h',
            'src/win/async.c',
            'src/win/atomicops-inl.h',
            'src/win/core.c',
            'src/win/dl.c',
            'src/win/error.c',
            'src/win/fs.c',
            'src/win/fs-event.c',
            'src/win/getaddrinfo.c',
            'src/win/handle.c',
            'src/win/handle-inl.h',
            'src/win/internal.h',
            'src/win/loop-watcher.c',
            'src/win/pipe.c',
            'src/win/thread.c',
            'src/win/poll.c',
            'src/win/process.c',
            'src/win/process-stdio.c',
            'src/win/req.c',
            'src/win/req-inl.h',
            'src/win/signal.c',
            'src/win/stream.c',
            'src/win/stream-inl.h',
            'src/win/tcp.c',
            'src/win/tty.c',
            'src/win/threadpool.c',
            'src/win/timer.c',
            'src/win/udp.c',
            'src/win/util.c',
            'src/win/winapi.c',
            'src/win/winapi.h',
            'src/win/winsock.c',
            'src/win/winsock.h',
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
        }, { # Not Windows i.e. POSIX
          'cflags': [
            '-g',
            '--std=gnu89',
            '-pedantic',
            '-Wall',
            '-Wextra',
            '-Wno-unused-parameter',
          ],
          'sources': [
            'include/uv-private/uv-unix.h',
            'include/uv-private/uv-linux.h',
            'include/uv-private/uv-sunos.h',
            'include/uv-private/uv-darwin.h',
            'include/uv-private/uv-bsd.h',
            'src/unix/async.c',
            'src/unix/core.c',
            'src/unix/dl.c',
            'src/unix/error.c',
            'src/unix/fs.c',
            'src/unix/getaddrinfo.c',
            'src/unix/internal.h',
            'src/unix/loop.c',
            'src/unix/loop-watcher.c',
            'src/unix/pipe.c',
            'src/unix/poll.c',
            'src/unix/process.c',
            'src/unix/signal.c',
            'src/unix/stream.c',
            'src/unix/tcp.c',
            'src/unix/thread.c',
            'src/unix/threadpool.c',
            'src/unix/timer.c',
            'src/unix/tty.c',
            'src/unix/udp.c',
          ],
          'link_settings': {
            'libraries': [ '-lm' ],
            'conditions': [
              ['OS=="solaris"', {
                'ldflags': [ '-pthreads' ],
              }, {
                'ldflags': [ '-pthread' ],
              }],
            ],
          },
          'conditions': [
            ['library=="shared_library"', {
              'cflags': [ '-fPIC' ],
            }],
            ['library=="shared_library" and OS!="mac"', {
              'link_settings': {
                # Must correspond with UV_VERSION_MAJOR and UV_VERSION_MINOR
                # in src/version.c
                'libraries': [ '-Wl,-soname,libuv.so.0.10' ],
              },
            }],
          ],
        }],
        [ 'OS=="linux" or OS=="mac"', {
          'sources': [ 'src/unix/proctitle.c' ],
        }],
        [ 'OS=="mac"', {
          'sources': [
            'src/unix/darwin.c',
            'src/unix/fsevents.c',
            'src/unix/darwin-proctitle.c',
          ],
          'link_settings': {
            'libraries': [
              '$(SDKROOT)/System/Library/Frameworks/Foundation.framework',
              '$(SDKROOT)/System/Library/Frameworks/CoreServices.framework',
              '$(SDKROOT)/System/Library/Frameworks/ApplicationServices.framework',
            ],
          },
          'defines': [
            '_DARWIN_USE_64_BIT_INODE=1',
          ]
        }],
        [ 'OS!="mac"', {
          # Enable on all platforms except OS X. The antique gcc/clang that
          # ships with Xcode emits waaaay too many false positives.
          'cflags': [ '-Wstrict-aliasing' ],
        }],
        [ 'OS=="linux"', {
          'sources': [
            'src/unix/linux-core.c',
            'src/unix/linux-inotify.c',
            'src/unix/linux-syscalls.c',
            'src/unix/linux-syscalls.h',
          ],
          'link_settings': {
            'libraries': [ '-ldl', '-lrt' ],
          },
        }],
        [ 'OS=="solaris"', {
          'sources': [ 'src/unix/sunos.c' ],
          'defines': [
            '__EXTENSIONS__',
            '_XOPEN_SOURCE=500',
          ],
          'link_settings': {
            'libraries': [
              '-lkstat',
              '-lnsl',
              '-lsendfile',
              '-lsocket',
            ],
          },
        }],
        [ 'OS=="aix"', {
          'include_dirs': [ 'src/ares/config_aix' ],
          'sources': [ 'src/unix/aix.c' ],
          'defines': [
            '_ALL_SOURCE',
            '_XOPEN_SOURCE=500',
          ],
          'link_settings': {
            'libraries': [
              '-lperfstat',
            ],
          },
        }],
        [ 'OS=="freebsd" or OS=="dragonflybsd"', {
          'sources': [ 'src/unix/freebsd.c' ],
        }],
        [ 'OS=="openbsd"', {
          'sources': [ 'src/unix/openbsd.c' ],
        }],
        [ 'OS=="netbsd"', {
          'sources': [ 'src/unix/netbsd.c' ],
        }],
        [ 'OS in "freebsd dragonflybsd openbsd netbsd".split()', {
          'link_settings': {
            'libraries': [ '-lkvm' ],
          },
        }],
        [ 'OS in "mac freebsd dragonflybsd openbsd netbsd".split()', {
          'sources': [ 'src/unix/kqueue.c' ],
        }],
        ['library=="shared_library"', {
          'defines': [ 'BUILDING_UV_SHARED=1' ]
        }],
        ['uv_use_dtrace=="true"', {
          'defines': [ 'HAVE_DTRACE=1' ],
          'dependencies': [ 'uv_dtrace_header' ],
          'include_dirs': [ '<(SHARED_INTERMEDIATE_DIR)' ],
          'conditions': [
            ['OS != "mac"', {
              'sources': ['src/unix/dtrace.c' ],
            }],
          ],
        }],
      ]
    },

    {
      'target_name': 'uv_dtrace_header',
      'type': 'none',
      'conditions': [
        [ 'uv_use_dtrace=="true"', {
          'actions': [
            {
              'action_name': 'uv_dtrace_header',
              'inputs': [ 'src/unix/uv-dtrace.d' ],
              'outputs': [ '<(SHARED_INTERMEDIATE_DIR)/uv-dtrace.h' ],
              'action': [ 'dtrace', '-h', '-xnolibs', '-s', '<@(_inputs)',
                '-o', '<@(_outputs)' ],
            },
          ],
        }],
      ],
    },

    {
      'target_name': 'uv_dtrace_provider',
      'type': 'none',
      'conditions': [
        [ 'uv_use_dtrace=="true" and OS!="mac"', {
          'actions': [
            {
              'action_name': 'uv_dtrace_o',
              'inputs': [
                'src/unix/uv-dtrace.d',
                '<(PRODUCT_DIR)/obj.target/libuv/<(uv_parent_path)/src/unix/core.o',
              ],
              'outputs': [
                '<(PRODUCT_DIR)/obj.target/libuv/<(uv_parent_path)/src/unix/dtrace.o',
              ],
              'action': [ 'dtrace', '-G', '-xnolibs', '-s', '<@(_inputs)',
                '-o', '<@(_outputs)' ]
            }
          ]
        } ]
      ]
    },

  ]
}

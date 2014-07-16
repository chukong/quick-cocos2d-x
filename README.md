根据我们的项目需要，我对 [quick-cocos2d-x][3] 做了一些修改。

这个版本基于 quick 被收购前停止更新几个月的过程中，quick社区推送多个pr后的最新的一个版本。quick 升级到 2.2.3 后有许多大的修改，例如更新player到QT，重写framework架构，对framework中的部分class进行重命名等等。由于对现有项目影响太大，我没有跟进。

所以，这个版本与目前的quick 2.2.3 不兼容。

这个版本主要进行了如下修改，这些修改有的已经同步到官方quick库中，有的则没有。

没有同步的原因同上。

2014-07-16 更新：

1. 更新 DragonBonesCPP 库到最新，解决一些内存泄露；
2. 为 CCAnimationCache/CCSpriteFrameCache 加入异步加载支持。

2014-07-09 更新：

1. 增加 samples/bytearray ；
2. 解决 ByteArray 的bug；
3. 删除 ByteArray:readLong/readULong/writeLong/writeULong，[原因见此][8] 。

2014-07-08 更新：

1. 修复 Mac/Win32 版本 player 的编译错误；
2. 删除 extensions/AssetsManager 模块，使用 extensions/updater 取而代之；
3. 删除 samples/ccarmature ，因为 CCArmature 已经被删除，sample当然也没用了；
4. 为 samples/dragonbones 加入了两个demo：SwitchClothes 和 ChaseStarling ；
5. 增加几个lua导出方法以支持新加入的两个 demo。

2014-06-25 更新：

1. 删除 CCB 支持，这个编辑器的开发早已停止，我并不使用它；
2. 删除 CCArmature，因为已经使用了DragonBonesCPP；
3. 加入 iOS 和 Android 的WebView组件，位于 extensions，详见：[在 cocos2d-x 中嵌入浏览器][7] 。

之前的更新：

1. 加入 [SocketTCP][4] 对 luasocket 进行了封装；
1. 模仿AS3用lua实现了 [ByteArray][5]；
1. 加入 [DragonBonesCPP][1] 组件，位于 extensions，使用 CCDragonBones.lua 进行了封装；
2. 加入 [cocos2d-x-filter][2] 组件，位于 extensioins，使用 filters.lua 进行了封装；
3. 加入了 CCDrawNodeExtend.lua 对 CCDrawNode 的常用方法进行封装；
4. 增加 printscreen, upload 等多个常用方法……

[1]: https://github.com/DragonBones/DragonBonesCPP
[2]: https://github.com/zrong/cocos2d-x-filters
[3]: https://github.com/chukong/quick-cocos2d-x
[4]: http://zengrong.net/post/1980.htm
[5]: http://zengrong.net/post/1968.htm
[6]: https://github.com/go3k/CCXWebview
[7]: http://zengrong.net/post/2123.htm
[8]: http://zengrong.net/post/2134.htm

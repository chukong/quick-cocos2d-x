根据我们的项目需要，我对 [quick-cocos2d-x][3] 做了一些修改。

这个版本基于 quick 被收购前停止更新几个月的过程中，quick社区推送多个pr后的最新的一个版本。quick 升级到 2.2.3 后有许多大的修改，例如更新player到QT，重写framework架构，对framework中的部分class进行重命名等等。由于对现有项目影响太大，我没有跟进。

所以，这个版本与目前的quick 2.2.3 不兼容。

这个版本主要进行了如下修改，这些修改有的已经同步到官方quick库中，有的则没有。

没有同步的原因同上。

1. 加入 [SocketTCP][4] 对 luasocket 进行了封装；
1. 模仿AS3用lua实现了 [ByteArray][5]；
1. 加入 [DragonBonesCPP][1] 组件，使用 CCDragonBones.lua 进行了封装；
2. 加入 [cocos2d-x-filter][2] 组件，使用 filters.lua 进行了封装；
3. 加入了 CCDrawNodeExtend.lua 对 CCDrawNode 的常用方法进行封装；
4. 增加 printscreen, upload 等多个常用方法……

[1]: https://github.com/DragonBones/DragonBonesCPP
[2]: https://github.com/zrong/cocos2d-x-filters
[3]: https://github.com/chukong/quick-cocos2d-x
[4]: http://zengrong.net/post/1980.htm
[5]: http://zengrong.net/post/1968.htm

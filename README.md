# simplegame_cocos2d-x
cocos2d-x を使った簡単なゲームコードのベース部分。
追加ソースのみ置いてあるので、その他の環境は自前でcocos2d-xをインストールする必要がある。

## ビルドまで

### luaの追加
プロジェクトにluaのソースを追加する。
lua.cとluac.c以外の全てのソースを、ディレクトリのルートに配置し、プロジェクト設定の"Search Paths"->"Header Search Paths"に
`$(SRCROOT)/../lua`を追加。

### C++17
プロジェクト設定の"Apple Clang - Language - C++" -> "C++ Language Dialect"を"C++17[-std=c++17]"、desktop側も同じように設定。

### マルチタッチ
proj.ios_mac/ios/RootViewController.mmにある、
```obj-c
- (void)loadView {
    // Initialize the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [UIScreen mainScreen].bounds
                                         pixelFormat: (__bridge NSString *)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: cocos2d::GLViewImpl::_multisamplingCount > 0 ? YES : NO
                                     numberOfSamples: cocos2d::GLViewImpl::_multisamplingCount ];
    
    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:YES]; // ←ここをYESにする。
    //[eaglView setMultipleTouchEnabled:NO];
    
    // Set EAGLView as view of RootViewController
    self.view = eaglView;
}
```

## 画像追加時の注意点
Xcodeで画像を追加する差異に、アトリビュートによってりんくできないことがある。
事前に以下のコマンでによって、属性を消してから、プロジェクトに追加する
```shell
$ xattr -cr [image.png]
```

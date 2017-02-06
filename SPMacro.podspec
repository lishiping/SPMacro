
Pod::Spec.new do |s|

  s.name         = "SPMacro"
  s.version      = "0.0.8"
  s.summary      = "Some very convenient macro definition code, developers use convenience.一些简单方便的宏定义帮助开发者快速使用"


  s.homepage     = "https://github.com/lishiping/SPMacro.git"
  s.license      = "LICENSE"
  # s.license      = { :type => "MIT", :file => "FILE_LICENSE" }

  s.author             = { "lishiping" => "83118274@qq.com" }

  s.ios.deployment_target = "6.0"

  s.source       = { :git => "https://github.com/lishiping/SPMacro.git", :tag => "0.0.8" }

   s.source_files  = 'SPMacro/SPMacro/*.{h,m,mm,cpp,c}', 'SPMacro/SPMacro/*/*.{h,m,mm,cpp,c}'
   s.public_header_files = 'SPMacro/SPMacro/*.h', 'SPMacro/SPMacro/*/*.h'

  s.frameworks  = 'UIKit','Foundation'
 #s.libraries   =  'runtime'

  s.requires_arc = true

 s.xcconfig = { "HEADER_SEARCH_PATHS" => "$(SDKROOT)/usr/include" }

end

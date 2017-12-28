
Pod::Spec.new do |s|

  s.name         = "SPMacro"
  s.version      = "0.2.0"
  s.summary      = "The macro of Foundation and UIKit,print,type,notification,threads,screen adaptation,colors etc. Foundation,UIKit层宏定义，打印，类型，通知，线程等，屏幕适配，颜色等"


  s.homepage     = "https://github.com/lishiping/SPMacro.git"
  s.license      = "LICENSE"
  # s.license      = { :type => "MIT", :file => "FILE_LICENSE" }

  s.author             = { "lishiping" => "83118274@qq.com" }

  s.ios.deployment_target = "7.0"

  s.source       = { :git => "https://github.com/lishiping/SPMacro.git", :tag => s.version }

   s.source_files  = 'SPMacro/SPMacro/*.{h,m,mm,cpp,c}', 'SPMacro/SPMacro/*/*.{h,m,mm,cpp,c}'
   s.public_header_files = 'SPMacro/SPMacro/*.h', 'SPMacro/SPMacro/*/*.h'

  s.frameworks  = 'UIKit','Foundation'
 #s.libraries   =  'runtime'

  s.requires_arc = true

 s.xcconfig = { "HEADER_SEARCH_PATHS" => "$(SDKROOT)/usr/include" }

end

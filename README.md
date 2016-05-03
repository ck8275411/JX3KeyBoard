# 剑三简单按键 
================================   
## 更新日志1.0.0：    
1. 修复由于子窗体OnPain()复写实现问题导致的CPU占用过高    
2. 修复监听程序频率过高导致的卡键盘问题    

## 功能介绍：
1. 仅支持同时按键；
2. "~"键开启和关闭；
3. 左“Alt”键暂停；
4. 支持自定义按键，仅支持数字、字母和不加shift的标点；
5. 同时按键的频率是100ms/次；     

## 使用说明：    
1. 驱动安装:    
在win7 64或者win8 win10上，需要复杂的过程安装winio驱动，如果怕中毒的，可以自行编译或者下载winio的驱动：     
  1.1 从开始菜单->搜索cmd->右键cmd，打开管理员模式的cmd->bcdedit /set testsigning on    
  1.2 然后修改WinIo64.sys的测试签名    
    a.打开 WinIO64.sys的属性框，翻到“数字签名”选项卡，点击“详细信息”    
    b.在新出来的对话框中点击“查看证书”   
    c.在又新出来的对话框中点击“安装证书”    
    d.点击“下一步”，然后选择“将所有的证书放入下列存储”   
    e.点击浏览，选择“受信任的根证书发布机构”    
    ![](https://github.com/ck8275411/JX3KeyBoard/blob/master/screenshots/135733q340en038u2s00gh.png)   
    f.点击完成，直到弹出警告框，并确认后，即表示成功    
    g.重启，屏幕右下角出现如下截图表示成功：    
    ![](https://github.com/ck8275411/JX3KeyBoard/blob/master/screenshots/151322mb3jf9cffq6mikcz.png)    
2. 安装VC2013的运行库；
3. 打开程序后，点击开始键开启"~"监听；
4. 打开程序后可能会有一个白框，那是前置悬浮窗口，用于显示“按键开启”和“按键关闭”，此时拖动主对话框，悬浮窗即可正常（请理解我写的程序之糙。。）    
![](https://github.com/ck8275411/JX3KeyBoard/blob/master/screenshots/135726kclzxvmxtx2gslff.png)

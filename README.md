功能：
    1.选择一个空的.txt文件，将自己遇到的不会的单词记录下来，随时可以通过软件查看和记忆；
    2.软件中接入了百度翻译的api，可以进行实时翻译；
    3.软件可以通过快捷键(CTRL + F9)翻译剪切板上的内容(弹窗显示翻译);
    更多功能正在开发中...

打算添加的功能：
    1.在"学音标"的窗口中，点击目标音标时播放对应的.mp3文件；    2023/9/28 已添加

目前存在的问题：
    1.剪切板中的文本带有符号时就翻译不了； 2023/9/27    [fix]2023/9/28
    2.剪切板中的文本带有'+'就不能翻译；    2023/9/28

注意事项：
    1.请用户自己申请百度翻译api，通过自己的id和密钥使用该软件；
    2.选择的.txt文件最好不要手动去更改内容;
    3.基于qt5.12.2开发;
    4.程序开始时会有一个填百度翻译api的ID和密钥的弹窗，最好使用自己申请的(可以暂时使用作者的，直接关闭弹窗即可)
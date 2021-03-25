#include "maininterface.h"
#include "ui_maininterface.h"

#ifdef Q_OS_ANDROID
#include<QAndroidJniEnvironment>
#include<QAndroidJniObject>
#include<QtAndroid>
#endif

#include<QDebug>
#include<iostream>

MainInterface::MainInterface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainInterface)
{
    ui->setupUi(this);

#ifdef Q_OS_ANDROID
        QAndroidJniEnvironment env;
       QAndroidJniObject m_activity = QtAndroid::androidActivity();
       //调用静态方法
        qDebug()<< m_activity.callStaticMethod<jint>("com/hjx/TestJNI",
                                    "test"
                                    //,"()V"//方法签名可以省略
                                    );

        jint num = 1;
        qDebug()<<m_activity.callStaticMethod<jint>("com/hjx/TestJNI",
                                         "test2",
                                         "(I)I",
                                         num);

        //调用静态类方法
        QAndroidJniObject obj = QAndroidJniObject::fromString("jiangxueHan");
        jstring jstr = obj.object<jstring>();
        QAndroidJniObject s = m_activity.callStaticObjectMethod("com/hjx/TestJNI",
                                                                "test3",
                                                   "(Ljava/lang/String;)Ljava/lang/String;",
                                                  jstr);

        //调用非静态方法
        QString qstring = s.toString();
        qDebug()<<qstring;

         m_activity.callMethod<void>("test4");

         //调用非静态类方法
        s =  m_activity.callObjectMethod("test5",
                                         "(Ljava/lang/String;)Ljava/lang/String;",
                                        jstr);
        qstring = s.toString();
        qDebug()<<qstring;

        if(env->ExceptionCheck()){
            env->ExceptionDescribe();
            env->ExceptionClear();
        }

#endif
}

MainInterface::~MainInterface()
{
    delete ui;
}


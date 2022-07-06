#pragma once
#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer // ����� �����
{
public:
    static cocos2d::Scene* createScene(); // ����� �������� �����
    bool init() override; // ����� �������������

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override; // ����
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override; // ��������� �����
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) override; // ����������� � ������� �������/�������
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) override; // ��������� ������/�����

    std::vector<cocos2d::Sprite*> sprites;
    std::vector<std::string> spr;

    float time{ 0 };

    int h;

    void update(float delta);

    CREATE_FUNC(HelloWorld); // ������, ������� ������������ � ���������� ��������� ������ �������������� GC (GarbageCollector ������ cocos-2dx)

};
#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <qt_windows.h>


class DisplaySetting 
{
    
public:
   DisplaySetting();
   DisplaySetting(const DisplaySetting&)=default;
   DisplaySetting& operator=(const DisplaySetting&) = default;
   
   DEVMODEW& devmodew();
   QString id() const;
   int freq() const;
   int height() const;
   int width()const;
   int color_depth() const;
   bool current() const;
   void set_current(bool);
   QVariant ToVariant()const;
   int Compare(const DisplaySetting&)const;

private:
    DEVMODEW devmodew_;
    bool current_; 
};


bool operator==(const DisplaySetting&l,const DisplaySetting& r);

size_t qHash(const DisplaySetting&v,size_t seed);

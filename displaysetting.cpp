#include "displaysetting.h"
#include <QUuid>
#include <qt_windows.h>
#include <QHash>


DisplaySetting::DisplaySetting() :
    devmodew_(),
    current_(false)
{
    ::memset(&devmodew_,0,sizeof(DEVMODEW));
    devmodew_.dmSize = sizeof(DEVMODE);   
}

QString DisplaySetting::id() const
{
    return QString::asprintf("%lld", qHashMulti(0,freq(),height(),width(),color_depth()));
}

DEVMODEW& DisplaySetting::devmodew()
{
    return devmodew_;
}

int DisplaySetting::freq() const{
    return devmodew_.dmDisplayFrequency;
}

int DisplaySetting::height() const{
    return devmodew_.dmPelsHeight;
}

int DisplaySetting::width()const{
    return devmodew_.dmPelsWidth;
}

int DisplaySetting::color_depth() const{
    return devmodew_.dmBitsPerPel;
}

QVariant DisplaySetting::ToVariant() const
{
    QVariantMap m;
    m.insert("id",id());
    m.insert("freq",freq());
    m.insert("height",height());
    m.insert("width",width());
    m.insert("color_depth",color_depth());
    m.insert("current",current());
    return m;
}

int DisplaySetting::Compare(const DisplaySetting &other) const
{
    if(width() != other.width()){
        return width() > other.width() ? 1: -1;
    }
    
    if(height() != other.height()){
        return height() > other.height() ? 1: -1;
    }
    return 0;
}

bool DisplaySetting::current() const
{
    return current_;
}

void DisplaySetting::set_current(bool newv)
{
    current_ = newv;
}

bool operator==(const DisplaySetting &l, const DisplaySetting &r){
   return l.freq() == r.freq() && 
            l.height() == r.height() &&
            l.width() == r.width() &&
            l.color_depth() == r.color_depth();
}

size_t qHash(const DisplaySetting &v, size_t seed)
{
    return qHashMulti(seed,v.freq(),v.height(),v.width(),v.color_depth());
}

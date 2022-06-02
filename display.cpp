#include "display.h"
#include <QDebug>
#include <QVariant>
#include <qt_windows.h>

Display::Display(QString device_name, QObject *parent)
    : QObject(parent),
      device_name_(device_name),
      ds_cache_()
{
}

QList<DisplaySetting>& Display::GetSettings(int refresh) {
    if(refresh){
        ds_cache_.clear();    
    }
    LPCWSTR dname = device_name_.length() == 0 ? nullptr: (LPCWSTR)device_name_.utf16();
    DWORD idx = -1;   
    QSet<DisplaySetting> ds_set;
    for(;;){
        DisplaySetting ds;
        ds.set_current(idx==-1);
        DEVMODEW& dm = ds.devmodew();
        BOOL ok = ::EnumDisplaySettingsW(dname,idx++,&dm);
        if(!ok){ break; }
        ds_set.insert(ds);   
    }
    std::copy(ds_set.cbegin(),ds_set.cend(),
              std::back_inserter(ds_cache_));     
    std::sort(ds_cache_.begin(),ds_cache_.end(),
              [](DisplaySetting&l, DisplaySetting&r){
                    return l.Compare(r) > 0;
              });
    return ds_cache_;
}

QVariantList Display::getSettings(int refresh)
{
   QVariantList out;
   auto& res = GetSettings(refresh);
   for(const auto& it : res){
      out.emplace_back(it.ToVariant());
   }
   return out;
}

DisplaySetting *Display::FindSetting(const QString& id)
{
    auto res = std::find_if(ds_cache_.begin(),ds_cache_.end(),
                            [&](const DisplaySetting& it){
        return it.id().compare(id)==0;
    });
    
    if(res == ds_cache_.end()){
        return nullptr;
    }
    return &*res;
}

int Display::ApplySetting(const QString& id)
{
    auto* settings = FindSetting(id);
    if(!settings){
        return 1;
    }
    auto* dmodew = &settings->devmodew();
    return (int)::ChangeDisplaySettingsW(dmodew,0);
}

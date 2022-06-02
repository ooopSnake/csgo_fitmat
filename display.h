#pragma once

#include <QObject>
#include "displaysetting.h"


class Display : public QObject
{
    Q_OBJECT    
public:
    Q_DISABLE_COPY_MOVE(Display)
    
    Display(QString device_name="", QObject *parent = nullptr);
    
    QList<DisplaySetting>& GetSettings(int refresh);
        
    // qml use only
    Q_INVOKABLE QVariantList getSettings(int refresh);
    
    /**
     * @brief FindSetting
     * @param id
     * @return maybe NULL
     */
    DisplaySetting* FindSetting(const QString& id);
    
    /**
     * @brief ApplySetting
     * @param id
     * @return 0: OK , other: failed
     */
    int ApplySetting(const QString& id);
    
    // qml use only
    Q_INVOKABLE int applySetting(const QString& id){
        return ApplySetting(id);
    }
    
private:
    QString device_name_;
    QList<DisplaySetting> ds_cache_;
};

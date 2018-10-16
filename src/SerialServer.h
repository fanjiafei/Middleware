#ifndef SERIALSERVER_H
#define SERIALSERVER_H
#include "Msg2MCUhandler.h"
#ifndef GDBUS //use qdbus
#include <QObject>
#include <QString>
#include "common.h"


class SerialServer: public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "Serial.interface")
public:
    SerialServer();
    ~SerialServer();

public slots:
    bool setDoorInfo(unsigned short arg1,unsigned short arg2);
    bool setLampInfo(unsigned short arg1,unsigned short arg2);
    bool setKeyInfo(unsigned short arg1,unsigned short arg2);
    bool setSpeedInfo(unsigned short arg1,unsigned short arg2,unsigned short arg3);
    bool setAirConditionerInfo(unsigned short arg1,unsigned short arg2,unsigned short arg3);
    bool setStartInfo(unsigned char arg1);
signals:
    /**
     * @brief broadcastCANInfo
     * @details 广播CAN数据
     * @param candata
     * @param len
     */
    void broadcastCANInfo(QByteArray candata,unsigned char len);

private:
    Msg2MCUhandler mMsg2MCUhandler;

};
#else //use gdbus
#include "gdbus/ServiceOfSerial.h"
class SerialServer
{
public:
    SerialServer();
    ~SerialServer();

    static void* taskSerialServer(void *arg);

    static void on_bus_acquired (GDBusConnection *connection,const gchar *name,gpointer user_data);

    static gboolean on_handle_set_door_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                                              guint16 arg1, guint16 arg2,gpointer user_data);
    static gboolean on_handle_set_lamp_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                                              guint16 arg1, guint16 arg2,gpointer user_data);
    static gboolean on_handle_set_key_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                                             guint16 arg1, guint16 arg2,gpointer user_data);
    static gboolean on_handle_set_speed_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                                               guint16 arg1, guint16 arg2,guint16 arg3,gpointer user_data);
    static gboolean on_handle_set_air_conditioner_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                                                         guint16 arg1, guint16 arg2,guint16 arg3,gpointer user_data);
    static gboolean on_handle_set_start_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                                               guint16 arg1,gpointer user_data);
    static void broadcastCANInfo(char *candata,unsigned char len);


};
#endif //dbus
#endif // SERIALSERVER_H

#include <sys/prctl.h>
#include "SerialServer.h"
#ifndef GDBUS
SerialServer::SerialServer()
{

}

SerialServer::~SerialServer()
{

}

/**
 * @brief SerialServer::setDoorInfo
 * @details 设置车门状态
 * @param arg1
 * @param arg2
 * @return
 */
bool SerialServer::setDoorInfo(unsigned short arg1,unsigned short arg2){
    UART_Dbg("called setDoorInfo arg1:%d arg2:%d\n",arg1,arg2);
    mMsg2MCUhandler.sendDoorInfo(arg1,arg2);
    return 1;
}
/**
 * @brief SerialServer::setLampInfo
 * @details 设置车灯状态
 * @param arg1
 * @param arg2
 * @return
 */
bool SerialServer::setLampInfo(unsigned short arg1,unsigned short arg2){
    UART_Dbg("called setLampInfo arg1:%d arg2:%d\n",arg1,arg2);
    mMsg2MCUhandler.sendLampInfo(arg1,arg2);
    return 1;
}
/**
 * @brief SerialServer::setKeyInfo
 * @details 设置车钥匙状态
 * @param arg1
 * @param arg2
 * @return
 */
bool SerialServer::setKeyInfo(unsigned short arg1,unsigned short arg2){
    mMsg2MCUhandler.sendKeyInfo(arg1,arg2);
    return 1;
}
/**
 * @brief SerialServer::setSpeedInfo
 * @details 设置车速状态
 * @param arg1
 * @param arg2
 * @param arg3
 * @return
 */
bool SerialServer::setSpeedInfo(unsigned short arg1,unsigned short arg2,unsigned short arg3){
    mMsg2MCUhandler.sendSpeedInfo(arg1,arg2,arg3);
    return 1;
}
/**
 * @brief SerialServer::setAirConditionerInfo
 * @details 设置空调状态
 * @param arg1
 * @param arg2
 * @param arg3
 * @return
 */
bool SerialServer::setAirConditionerInfo(unsigned short arg1,unsigned short arg2,unsigned short arg3){
    mMsg2MCUhandler.sendAirConditionerInfo(arg1,arg2,arg3);
    return 1;
}
/**
 * @brief SerialServer::setStartInfo
 * @details 设置start状态
 * @param arg1
 * @return
 */
bool SerialServer::setStartInfo(unsigned char arg1){
    mMsg2MCUhandler.sendStartInfo(arg1);
    return 1;
}

#else //GDBUS
#include "common.h"

static SerialInterface *skeleton;

SerialServer::SerialServer()
{
    if(skeleton==NULL)
        skeleton = serial_interface_skeleton_new();
}

SerialServer::~SerialServer()
{

}
void SerialServer::broadcastCANInfo(char *candata,unsigned char len){

    serial_interface_emit_broadcast_caninfo(skeleton,candata,len);
}

gboolean SerialServer::on_handle_set_door_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                          guint16 arg1, guint16 arg2,gpointer user_data)
{
    Msg2MCUhandler mMsg2MCUhandler;
    UART_Dbg("called setDoorInfo arg1:%d arg2:%d\n",arg1,arg2);
    mMsg2MCUhandler.sendDoorInfo(arg1,arg2);
    serial_interface_complete_set_door_info(object,invocation,arg1*arg2);
    return 1;
}

gboolean SerialServer::on_handle_set_lamp_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                          guint16 arg1, guint16 arg2,gpointer user_data)
{
    Msg2MCUhandler mMsg2MCUhandler;
    UART_Dbg("called sendLampInfo arg1:%d arg2:%d\n",arg1,arg2);
    mMsg2MCUhandler.sendLampInfo(arg1,arg2);
    serial_interface_complete_set_lamp_info(object,invocation,arg1*arg2);
    return 1;
}

gboolean SerialServer::on_handle_set_key_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                          guint16 arg1, guint16 arg2,gpointer user_data)
{
    Msg2MCUhandler mMsg2MCUhandler;
    UART_Dbg("called sendKeyInfo arg1:%d arg2:%d\n",arg1,arg2);
    mMsg2MCUhandler.sendKeyInfo(arg1,arg2);
    serial_interface_complete_set_key_info(object,invocation,arg1*arg2);
    return 1;
}

gboolean SerialServer::on_handle_set_speed_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                          guint16 arg1, guint16 arg2,guint16 arg3,gpointer user_data)
{
    Msg2MCUhandler mMsg2MCUhandler;
    UART_Dbg("called sendSpeedInfo arg1:%d arg2:%d arg3:%d\n",arg1,arg2,arg3);
    mMsg2MCUhandler.sendSpeedInfo(arg1,arg2,arg3);
    serial_interface_complete_set_speed_info(object,invocation,arg1*arg2);
    return 1;
}

gboolean SerialServer::on_handle_set_air_conditioner_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                          guint16 arg1, guint16 arg2,guint16 arg3,gpointer user_data)
{
    Msg2MCUhandler mMsg2MCUhandler;
    UART_Dbg("called sendAirConditionerInfo arg1:%d arg2:%d\n",arg1,arg2);
    mMsg2MCUhandler.sendAirConditionerInfo(arg1,arg2,arg3);
    serial_interface_complete_set_air_conditioner_info(object,invocation,arg1*arg2);
    return 1;
}


gboolean SerialServer::on_handle_set_start_info ( SerialInterface *object,GDBusMethodInvocation *invocation,
                          guint16 arg1,gpointer user_data)
{
    Msg2MCUhandler mMsg2MCUhandler;
    UART_Dbg("called sendStartInfo arg1:%d\n",arg1);
    mMsg2MCUhandler.sendStartInfo(arg1);
    serial_interface_complete_set_start_info(object,invocation,arg1);
    return 1;
}

void SerialServer::on_bus_acquired (GDBusConnection *connection,
                 const gchar     *name,
                 gpointer         user_data){

    g_signal_connect (skeleton,"handle-set-door-info",G_CALLBACK (on_handle_set_door_info),NULL);
    g_signal_connect (skeleton,"handle-set-lamp-info",G_CALLBACK (on_handle_set_lamp_info),NULL);
    g_signal_connect (skeleton,"handle-set-key-info",G_CALLBACK (on_handle_set_key_info),NULL);
    g_signal_connect (skeleton,"handle-set-speed-info",G_CALLBACK (on_handle_set_speed_info),NULL);
    g_signal_connect (skeleton,"handle-set-air-conditioner-info",G_CALLBACK (on_handle_set_air_conditioner_info),NULL);
    g_signal_connect (skeleton,"handle-set-start-info",G_CALLBACK (on_handle_set_start_info),NULL);

    g_dbus_interface_skeleton_export (G_DBUS_INTERFACE_SKELETON (skeleton),connection,"/serial/service",NULL);
}


void* SerialServer::taskSerialServer(void *arg){
    GMainLoop *loop;
    prctl(PR_SET_NAME,(unsigned long)"SerialServer");
    UART_Dbg("[start] taskSerialServer\n");
    if(skeleton==NULL)
        skeleton = serial_interface_skeleton_new();
    loop = g_main_loop_new (NULL, FALSE);
    g_bus_own_name (G_BUS_TYPE_SESSION,
            "Serial.interface",
            G_BUS_NAME_OWNER_FLAGS_NONE,
            NULL,
            on_bus_acquired,
            NULL,
            NULL,
            NULL);

    g_main_loop_run (loop);
}

#endif //GDBUS

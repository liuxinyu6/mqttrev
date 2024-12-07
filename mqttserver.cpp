#include "mqttserver.h"
#include <cstring>
#include <QDebug>
/*
template <class T>
MqttServer<T>::MqttServer(const char* addr, int port,
                          const char* username, const char* password, T* compose):
    _port(port),_compose(compose)
{
    strcpy(_addr, addr);
    strcpy(_username, username);
    strcpy(_password, password);
}

template  <class T>
MqttServer<T>::~MqttServer()
{
    if(_mos)
    {
        mosquitto_destroy(_mos);
    }
    mosquitto_lib_cleanup();
}

template  <class T>
bool MqttServer<T>::Init()
{
    int ret = mosquitto_lib_init();
    if(MOSQ_ERR_SUCCESS != ret)
    {
        qDebug()<<"mosquitto_lib_init failed,"<<mosquitto_strerror(ret);
        return false;
    }
    _mos = mosquitto_new(nullptr, true, _compose);
    if(nullptr == _mos)
    {
        qDebug()<<"mosquitto_new failed,"<<mosquitto_strerror(errno);
        return false;
    }

    mosquitto_username_pw_set(_mos,_username,_password);

    mosquitto_connect_callback_set(_mos, MqttServer<T>::on_connect);
    mosquitto_disconnect_callback_set(_mos, MqttServer<T>::on_disconnect);
    mosquitto_subscribe_callback_set(_mos, MqttServer<T>::on_subscribe);
    mosquitto_message_callback_set(_mos, MqttServer<T>::on_message);

    return true;
}

template <class T>
void MqttServer<T>::on_connect(struct mosquitto * mos, void *userdata, int result)
{
    if(result != 0)
    {
        //重连
        qDebug()<<"connect failed: "<<mosquitto_strerror(result);
        mosquitto_reconnect(mos);
    }
    else
    {
        qDebug()<<"connect success";
    }
}

template <class T>
void MqttServer<T>::on_disconnect(struct mosquitto *mos, void *userdata, int result)
{
    if(result == 0)
    {
        //重连
        qDebug()<<"disconnect success";
        mosquitto_reconnect(mos);
    }
}

template <class T>
void MqttServer<T>::on_subscribe(struct mosquitto *mos, void *userdata, int, int, const int *)
{

}

template <class T>
void MqttServer<T>::on_message(struct mosquitto *mos, void *userdata, const struct mosquitto_message *msg)
{
    qDebug()<<"message get, topic:"<<msg->topic;

    if(userdata != nullptr)
    {
        T* _compose = (T*)userdata;
        _compose->proc(msg->payload, msg->payloadlen);
    }
}

template  <class T>
int MqttServer<T>::Connect(int keepalive)
{
    int ret = mosquitto_connect(_mos, _addr, _port, keepalive);
    if(MOSQ_ERR_SUCCESS != ret)
    {
        qDebug()<<"mosquitto_connect failed,"<<mosquitto_strerror(ret);
    }
    return ret;
}

template <class T>
int MqttServer<T>::Subsribe(int *mid, const char *sub, int qos)
{
    int ret = mosquitto_subscribe(_mos, mid, sub, qos);
    if(MOSQ_ERR_SUCCESS != ret)
    {
        qDebug()<<"mosquitto_subscribe failed,"<<mosquitto_strerror(ret);
    }
    return ret;
}

template  <class T>
int MqttServer<T>::Loop(int timeout, int max_packets)
{
    int ret = mosquitto_loop_forever(_mos, timeout, max_packets);
    if(MOSQ_ERR_SUCCESS != ret)
    {
        qDebug()<<"loop failed,"<<mosquitto_strerror(ret);
    }
    return ret;
}
*/



#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include "mosquitto.h"
#include <cerrno>
#include <QDebug>

template  <class T>
class MqttServer
{
public:
    MqttServer(const char* addr = "127.0.0.1", int port = 1883,
               const char* username = nullptr, const char* password = nullptr, T* compose = nullptr)
        :_port(port), _compose(compose)
    {
        strcpy(_addr, addr);
        strcpy(_username, username);
        strcpy(_password, password);
    }
    ~MqttServer()
    {
        if(_mos)
        {
            mosquitto_destroy(_mos);
        }
        mosquitto_lib_cleanup();
    }

    bool Init()
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

 //       mosquitto_username_pw_set(_mos,_username,_password);

        mosquitto_connect_callback_set(_mos, MqttServer::on_connect);
        mosquitto_disconnect_callback_set(_mos, MqttServer::on_disconnect);
        mosquitto_subscribe_callback_set(_mos, MqttServer::on_subscribe);
        mosquitto_message_callback_set(_mos, MqttServer::on_message);

        return true;
    }

    int Connect(int keepalive)
    {
        qDebug()<<QString(_addr)<<" "<<_port;
        int ret = mosquitto_connect(_mos, _addr, _port, keepalive);
        if(MOSQ_ERR_SUCCESS != ret)
        {
            qDebug()<<ret<<" mosquitto_connect failed,"<<mosquitto_strerror(ret);
        }
        return ret;
    }
    int Subsribe(int *mid, const char *sub, int qos)
    {
        int ret = mosquitto_subscribe(_mos, mid, sub, qos);
        if(MOSQ_ERR_SUCCESS != ret)
        {
            qDebug()<<"mosquitto_subscribe failed,"<<mosquitto_strerror(ret);
        }
        return ret;
    }
    int Loop(int timeout,int max_packets)
    {
        int ret = mosquitto_loop_forever(_mos, timeout, max_packets);
        if(MOSQ_ERR_SUCCESS != ret)
        {
            qDebug()<<"loop failed,"<<mosquitto_strerror(ret);
        }
        return ret;
    }

public:
        static void on_connect(struct mosquitto * mos, void *userdata, int result)
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
        static void on_disconnect(struct mosquitto *mos, void *userdata, int result)
        {
            if(result == 0)
            {
                //重连
                qDebug()<<"disconnect success";
                mosquitto_reconnect(mos);
            }
        }
        static void on_subscribe(struct mosquitto *mos, void *userdata, int, int, const int *)
        {

        }
        static void on_message(struct mosquitto *mos, void *userdata, const struct mosquitto_message *msg)
        {
            /*
            qDebug()<<"message get, topic:"<<msg->topic;
            unsigned char* data = (unsigned char*)msg->payload;
            for(int n = 0; n < msg->payloadlen; n++)
            {
                QString hexString = QString::number(data[n], 16).toUpper();
                qDebug() << hexString <<" ";
            }
            */
            if(userdata != nullptr)
            {
                T* xcompose = (T*)userdata;
                xcompose->proc(msg->payload, msg->payloadlen);
            }
        }

private:
    int _port;
    const static int addrlen{1024};
    char _addr[addrlen];

    const static int infolen{100};
    char _username[infolen];
    char _password[infolen];

    mosquitto* _mos;
    T* _compose;
};

#endif // MQTTCLIENT_H

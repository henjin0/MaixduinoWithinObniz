#include <obniz.h>
#include<string.h>

void onCommand(uint8_t* data, uint16_t length){
  Serial.printf("%s",data);
}


bool isOnline = false;

void onEvent(os_event_t event, uint8_t* data, uint16_t length) {
  switch (event) {
  case PLUGIN_EVENT_NETWORK_CLOUD_CONNECTED:
    Serial.println("cloud Connected");
    isOnline = true;
    break;
  case PLUGIN_EVENT_NETWORK_CLOUD_DISCONNECTED:
    Serial.println("cloud Disconnected");
    isOnline = false;
    break;
  case PLUGIN_EVENT_NETWORK_HARDWARE_CONNECTED:
  case PLUGIN_EVENT_NETWORK_HARDWARE_DISCONNECTED:
  case PLUGIN_EVENT_NETWORK_WIFI_SCANNING:
  case PLUGIN_EVENT_NETWORK_WIFI_NOTFOUND:
  case PLUGIN_EVENT_NETWORK_WIFI_CONNECTING:
  case PLUGIN_EVENT_NETWORK_WIFI_SOFTAP_CONNECTED:
  case PLUGIN_EVENT_NETWORK_WIFI_FAIL:
  case PLUGIN_EVENT_FAIL:
  case PLUGIN_EVENT_OTA_START:
  case PLUGIN_EVENT_OTA_END:
  case PLUGIN_EVENT_OTA_ERROR:
  case PLUGIN_EVENT_INITIALIZED:
    break;
  }
}


void setup() {
  Serial.begin(115200);

  obniz.commandReceive(onCommand);
  obniz.onEvent(onEvent);
  
  obniz.start(NULL);//NULL =  obnizOS serial not used for log

  while(!obniz.getId());
  Serial.printf("obnizID : %s\n",obniz.getId());
  Serial.printf("obnizOS : %s\n",obniz.getOsVersion());
}

uint8_t val[1024];
int i = 0;
void loop() {
  if(isOnline){

      if (Serial.available() > 0){
        val[i]= (uint8_t)Serial.read();

        if(val[i]==0 || val[i]==10){
          obniz.commandSend(val,i);
          i = 0;
        }else{
          i++;
        }
      }  
  }
}

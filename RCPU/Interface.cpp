#include "Interface.h"
#include "DeviceManger.h"
#include "ConfigManger.h"
#include "AlarmManger.h"
#include "WebServiceManger.h"
#include "PMSManger.h"

CInterface::CInterface()
{
	
}


CInterface::~CInterface()
{
}

void CInterface::Start()
{
	ConfigManger = new CConfigManger;
	ConfigManger->Start();
	HPR_Sleep(100);

	WebServiceManger = new CWebServiceManger(ConfigManger);
	WebServiceManger->Start();

	PMSManger = new CPMSManger(WebServiceManger);
	PMSManger->Start();

	DeviceManger = new CDeviceManger;
	DeviceManger->Start();
	
	AlarmManger = new CAlarmManger(DeviceManger, PMSManger);
	AlarmManger->Start();
}

void CInterface::Close()
{

}

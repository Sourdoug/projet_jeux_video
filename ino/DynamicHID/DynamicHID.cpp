#include "DynamicHID.h"

#if defined(USBCON)

#ifdef _VARIANT_ARDUINO_DUE_X_
#define USB_SendControl USBD_SendControl
#define USB_Send USBD_Send
#endif

DynamicHID_& DynamicHID()
{
	static DynamicHID_ obj;
	return obj;
}

int DynamicHID_::getInterface(uint8_t* interfaceCount)
{
	*interfaceCount += 1; 
	DYNAMIC_HIDDescriptor hidInterface = {
		D_INTERFACE(pluggedInterface, 1, USB_DEVICE_CLASS_HUMAN_INTERFACE, DYNAMIC_HID_SUBCLASS_NONE, DYNAMIC_HID_PROTOCOL_NONE),
		D_HIDREPORT(descriptorSize),
		D_ENDPOINT(USB_ENDPOINT_IN(pluggedEndpoint), USB_ENDPOINT_TYPE_INTERRUPT, USB_EP_SIZE, 0x01)
	};
	return USB_SendControl(0, &hidInterface, sizeof(hidInterface));
}

int DynamicHID_::getDescriptor(USBSetup& setup)
{
	
	if (setup.bmRequestType != REQUEST_DEVICETOHOST_STANDARD_INTERFACE) { return 0; }
	if (setup.wValueH != DYNAMIC_HID_REPORT_DESCRIPTOR_TYPE) { return 0; }

	
	if (setup.wIndex != pluggedInterface) { return 0; }

	int total = 0;
	DynamicHIDSubDescriptor* node;
	for (node = rootNode; node; node = node->next) {
		int res = USB_SendControl((node->inProgMem ? TRANSFER_PGM : 0), node->data, node->length);
		if (res == -1)
			return -1;
		total += res;
	}
	
	
	protocol = DYNAMIC_HID_REPORT_PROTOCOL;
	
	return total;
}

uint8_t DynamicHID_::getShortName(char *name)
{
	name[0] = 'H';
	name[1] = 'I';
	name[2] = 'D';
	name[3] = 'A' + (descriptorSize & 0x0F);
	name[4] = 'A' + ((descriptorSize >> 4) & 0x0F);
	return 5;
}

void DynamicHID_::AppendDescriptor(DynamicHIDSubDescriptor *node)
{
	if (!rootNode) {
		rootNode = node;
	} else {
		DynamicHIDSubDescriptor *current = rootNode;
		while (current->next) {
			current = current->next;
		}
		current->next = node;
	}
	descriptorSize += node->length;
}

int DynamicHID_::SendReport(uint8_t id, const void* data, int len)
{
	uint8_t p[len + 1];
	p[0] = id;
	memcpy(&p[1], data, len);
	return USB_Send(pluggedEndpoint | TRANSFER_RELEASE, p, len + 1);
}

bool DynamicHID_::setup(USBSetup& setup)
{
	if (pluggedInterface != setup.wIndex) {
		return false;
	}

	uint8_t request = setup.bRequest;
	uint8_t requestType = setup.bmRequestType;

	if (requestType == REQUEST_DEVICETOHOST_CLASS_INTERFACE)
	{
		if (request == DYNAMIC_HID_GET_REPORT) {
			
			return true;
		}
		if (request == DYNAMIC_HID_GET_PROTOCOL) {
			
			return true;
		}
		if (request == DYNAMIC_HID_GET_IDLE) {
			
		}
	}

	if (requestType == REQUEST_HOSTTODEVICE_CLASS_INTERFACE)
	{
		if (request == DYNAMIC_HID_SET_PROTOCOL) {
			
			protocol = setup.wValueL;
			return true;
		}
		if (request == DYNAMIC_HID_SET_IDLE) {
			idle = setup.wValueL;
			return true;
		}
		if (request == DYNAMIC_HID_SET_REPORT)
		{
			
		}
	}

	return false;
}

DynamicHID_::DynamicHID_(void) : PluggableUSBModule(1, 1, epType),
                   rootNode(NULL), descriptorSize(0),
                   protocol(DYNAMIC_HID_REPORT_PROTOCOL), idle(1)
{
	epType[0] = EP_TYPE_INTERRUPT_IN;
	PluggableUSB().plug(this);
}

int DynamicHID_::begin(void)
{
	return 0;
}

#endif 
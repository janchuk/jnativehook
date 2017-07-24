/* JNativeHook: Global keyboard and mouse hooking for Java.
 * Copyright (C) 2006-2017 Alexander Barker.  All Rights Received.
 * https://github.com/kwhat/jnativehook/
 *
 * JNativeHook is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * JNativeHook is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <jni.h>
#include <uiohook.h>

#include "jni_Converter.h"
#include "org_jnativehook_NativeInputEvent.h"
#include "org_jnativehook_keyboard_NativeKeyEvent.h"
#include "org_jnativehook_mouse_NativeMouseEvent.h"
#include "org_jnativehook_mouse_NativeMouseWheelEvent.h"


jint jni_ConvertToJavaType(event_type nativeType, jint *javaType) {
	jint status = JNI_ERR;

	if (javaType != NULL) {
		switch (nativeType) {
			case EVENT_KEY_TYPED:
			case EVENT_KEY_PRESSED:
			case EVENT_KEY_RELEASED:
				// 3 = EVENT_HOOK_ENABLED + EVENT_HOOK_DISABLED + UNDEFINED.
				*javaType = org_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_FIRST + (nativeType - 3);
				status = JNI_OK;
				break;

			case EVENT_MOUSE_CLICKED:
			case EVENT_MOUSE_PRESSED:
			case EVENT_MOUSE_RELEASED:
			case EVENT_MOUSE_MOVED:
			case EVENT_MOUSE_DRAGGED:
			case EVENT_MOUSE_WHEEL:
				// 6 = (NATIVE_KEY_LAST - NATIVE_KEY_FIRST) + EVENT_HOOK_ENABLED + EVENT_HOOK_DISABLED + UNDEFINED.
				*javaType = org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_FIRST + (nativeType - 6);
				status = JNI_OK;
				break;

			default:
				*javaType = 0;
				break;
		}
	}

	return status;
}


jint jni_ConvertToNativeType(jint javaType, event_type *nativeType) {
	jint status = JNI_ERR;

	if (nativeType != NULL) {
		switch (javaType) {
			case org_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_TYPED:
			case org_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_PRESSED:
			case org_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_RELEASED:
				*nativeType = (javaType + 3) - org_jnativehook_keyboard_NativeKeyEvent_NATIVE_KEY_FIRST;
				status = JNI_OK;
				break;

			case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_CLICKED:
			case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_PRESSED:
			case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_RELEASED:
			case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_MOVED:
			case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_DRAGGED:
			case org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_WHEEL:
				*nativeType = (javaType + 6) - org_jnativehook_mouse_NativeMouseEvent_NATIVE_MOUSE_FIRST;
				status = JNI_OK;
				break;

			default:
				*nativeType = 0;
				break;
		}
	}

	return status;
}

jint jni_ConvertToJavaLocation(unsigned short int nativeKeyCode, jint *javaKeyLocation) {
	jint status = JNI_ERR;

	if (javaKeyLocation != NULL) {
		switch (nativeKeyCode) {
			case VC_SHIFT_L:
			case VC_CONTROL_L:
			case VC_ALT_L:
			case VC_META_L:
				*javaKeyLocation = org_jnativehook_keyboard_NativeKeyEvent_LOCATION_LEFT;
				break;

			case VC_SHIFT_R:
			case VC_CONTROL_R:
			case VC_ALT_R:
			case VC_META_R:
				*javaKeyLocation = org_jnativehook_keyboard_NativeKeyEvent_LOCATION_RIGHT;
				break;

			case VC_KP_0:
			case VC_KP_1:
			case VC_KP_2:
			case VC_KP_3:
			case VC_KP_4:
			case VC_KP_5:
			case VC_KP_6:
			case VC_KP_7:
			case VC_KP_8:
			case VC_KP_9:

			case VC_NUM_LOCK:
			case VC_KP_ENTER:
			case VC_KP_MULTIPLY:
			case VC_KP_ADD:
			case VC_KP_SEPARATOR:
			case VC_KP_SUBTRACT:
			case VC_KP_DIVIDE:
			case VC_KP_COMMA:
				*javaKeyLocation = org_jnativehook_keyboard_NativeKeyEvent_LOCATION_NUMPAD;
				break;

			default:
				*javaKeyLocation = org_jnativehook_keyboard_NativeKeyEvent_LOCATION_STANDARD;
				break;
		}

		status = JNI_OK;
	}

	return status;
}

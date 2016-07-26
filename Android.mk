LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/arrow.cpp \
				   ../../Classes/ArrowPathBezier.cpp \
				   ../../Classes/Board.cpp \
				   ../../Classes/Circle.cpp \
				   ../../Classes/contact_data.h \
				   ../../Classes/deadstar.cpp \
				   ../../Classes/GameDirectory.cpp \
				   ../../Classes/GameOverScene.cpp \
				   ../../Classes/Ground.cpp \
				   ../../Classes/HelpScene.cpp \
				   ../../Classes/Hero.cpp \
				   ../../Classes/HomeScene.cpp \
				   ../../Classes/monsterA.cpp \
				   ../../Classes/monsterB.cpp \
				   ../../Classes/monsterC.cpp \
				   ../../Classes/monsterD.cpp \
				   ../../Classes/MyUtility.cpp \
				   ../../Classes/obstacle.cpp \
				   ../../Classes/PlayMapOne.cpp \
				   ../../Classes/PlayMapTwo.cpp \
				   ../../Classes/PlayMapThree.cpp \
				   ../../Classes/PlayMapFour.cpp \
				   ../../Classes/PlayMapFive.cpp \
				   ../../Classes/PlayMapSix.cpp \
				   ../../Classes/PlayMapSeven.cpp \
				   ../../Classes/PlayMapEight.cpp \
				   ../../Classes/PlayMapNine.cpp \
				   ../../Classes/PlaySceneOne.cpp \
				   ../../Classes/PlaySceneTwo.cpp \
				   ../../Classes/PlaySceneThree.cpp \
				   ../../Classes/PlaySceneFour.cpp \
				   ../../Classes/PlaySceneFive.cpp \
				   ../../Classes/PlaySceneSix.cpp \
				   ../../Classes/PlaySceneSeven.cpp \
				   ../../Classes/PlaySceneEight.cpp \
				   ../../Classes/PlaySceneNine.cpp \
				   ../../Classes/SettingScene.cpp \
				   ../../Classes/SystemHeader.h \
				   ../../Classes/TeamScene.cpp \
				   ../../Classes/WayScene.cpp \
                    ../../Classes/newScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

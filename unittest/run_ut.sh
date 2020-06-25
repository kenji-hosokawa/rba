#!/bin/sh

./unittest_rba --gtest_filter=-HA497_JsonParser_Sound.*\
:HA497_AllocatedContent_LhsBeforeArbitrate.Test_1\
:HA497_ReArbitration_HasComeEarlierThan.Test_1\
:HA497_HasComeEarlierThan_Zone.Test_1\
:HA497_HasComeEarlierThan_Zone.Test_2\
:HA497_Scene_CallAPI.getPropertyValue\
:HA497_Result_CallAPI.getAttenuatedZones\
:HA497_Result_CallAPI.getCanceledViewContents\
:HA497_Result_CallAPI.getCanceledSoundContents\
:HA497_ViewAction_Exception.TRANSITION_ADD\
:HA497_ViewAction_Exception.TRANSITION_REMOVE\
:HA497_ViewAction_Exception.TRANSITION_REPLACE\
:HA497_ViewAction_Exception.MOVE\
:HA497_ViewContent_CallAPI.getLoserType\
:HA497_SetProperty_pre.Test_1\
:HA497_SoundContentState_CallAPI.getOrder\
:HA497_SoundContent_CallAPI.getLoserType\
:HA497_ViewContentState_CallAPI.getOrder


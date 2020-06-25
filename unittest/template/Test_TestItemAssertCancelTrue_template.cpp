  elems = {<INPUT_PARAMS>};
  {
    std::string kind = elems[1];
    std::string contextName = elems[2]+'/'+elems[3];
    rba::RBAViewContentState* state
      = arb->getModel()->findViewContentState(contextName);
    if(state){
      ASSERT_NE(nullptr, state);
      // check active
      EXPECT_TRUE(result->isCancel(state));
    }else{
      rba::RBASoundContentState* state = arb->getModel()->findSoundContentState(contextName);
      ASSERT_NE(nullptr, state);
      // check active
      EXPECT_TRUE(result->isCancel(state));
    }
  }

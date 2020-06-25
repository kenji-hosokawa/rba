  elems = {<INPUT_PARAMS>};
  {
    ASSERT_EQ(3U, elems.size());
    ASSERT_STRNE("", elems[0].c_str());
    ASSERT_STRNE("", elems[1].c_str());
    ASSERT_STRNE("", elems[2].c_str());
    std::string kind = elems[1];
    std::string scene = elems[2];
    result = arb->execute(scene, true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

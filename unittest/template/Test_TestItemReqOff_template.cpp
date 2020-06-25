  elems = {<INPUT_PARAMS>};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name, false); // OFF
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

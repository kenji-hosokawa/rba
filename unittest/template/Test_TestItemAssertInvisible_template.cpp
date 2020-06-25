  elems = {<INPUT_PARAMS>};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check invisible
      EXPECT_FALSE(result->isVisible(area));
      if(result->isVisible(area) == true) {
        std::cerr << "AREA: " << area->getName() << std::endl;
        std::cerr << "CONTENT: " << result->getContentState(area)->getOwner()->getName() << std::endl;
      }
    }
    else {
      // check zone
      rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check invisible
      EXPECT_FALSE(result->isSounding(zone));
      if(result->isSounding(zone) == true) {
        std::cerr << "ZONE: " << zone->getName() << std::endl;
        std::cerr << "CONTENT: " << result->getContentState(zone)->getOwner()->getName() << std::endl;
      }
    }
  }

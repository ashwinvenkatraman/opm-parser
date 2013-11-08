/*
  Copyright 2013 Statoil ASA.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */

#define BOOST_TEST_MODULE ScheduleIntegrationTests
#include <math.h>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <opm/parser/eclipse/Deck/Deck.hpp>
#include <opm/parser/eclipse/Parser/Parser.hpp>
#include <opm/parser/eclipse/EclipseState/Schedule/Schedule.hpp>


using namespace Opm;

BOOST_AUTO_TEST_CASE(CreateSchedule) {

    ParserPtr parser(new Parser());
    boost::filesystem::path scheduleFile("testdata/integration_tests/SCHEDULE/SCHEDULE1");
    DeckPtr deck = parser->parse(scheduleFile.string());
    ScheduleConstPtr sched(new Schedule(deck));
    TimeMapConstPtr timeMap = sched->getTimeMap();
    BOOST_CHECK_EQUAL(boost::gregorian::date(2007, boost::gregorian::May, 10), sched->getStartDate());
    BOOST_CHECK_EQUAL(9U, timeMap->size());

}

BOOST_AUTO_TEST_CASE(WellTesting) {
    ParserPtr parser(new Parser());
    boost::filesystem::path scheduleFile("testdata/integration_tests/SCHEDULE/SCHEDULE_WELLS2");
    DeckPtr deck = parser->parse(scheduleFile.string());
    ScheduleConstPtr sched(new Schedule(deck));

    BOOST_CHECK_EQUAL(3U, sched->numWells());
    BOOST_CHECK(sched->hasWell("OP_1"));
    BOOST_CHECK(sched->hasWell("OP_2"));
    BOOST_CHECK(sched->hasWell("OP_3"));

    {
        WellPtr well1 = sched->getWell("OP_1");

        BOOST_CHECK(well1->isInPredictionMode(0));
        BOOST_CHECK_EQUAL(0, well1->getOilRate(0));

        BOOST_CHECK_EQUAL(0, well1->getOilRate(1));
        BOOST_CHECK_EQUAL(0, well1->getOilRate(2));
        
        BOOST_CHECK(!well1->isInPredictionMode(3));
        BOOST_CHECK_EQUAL(4000, well1->getOilRate(3));
        BOOST_CHECK_EQUAL(4000, well1->getOilRate(4));
        BOOST_CHECK_EQUAL(4000, well1->getOilRate(5));

        BOOST_CHECK(!well1->isInPredictionMode(6));
        BOOST_CHECK_EQUAL(14000, well1->getOilRate(6));
        
        BOOST_CHECK(well1->isInPredictionMode(7));
        BOOST_CHECK_EQUAL(11000, well1->getOilRate(7));
        
        BOOST_CHECK(!well1->isInPredictionMode(8));
        BOOST_CHECK_EQUAL(13000, well1->getOilRate(8));
        BOOST_CHECK_EQUAL(13000, well1->getOilRate(9));
        BOOST_CHECK_EQUAL(13000, well1->getOilRate(10));
    }
}

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

#define BOOST_TEST_MODULE ParserIntegrationTests
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include <opm/parser/eclipse/Deck/Deck.hpp>

#include <opm/parser/eclipse/Parser/Parser.hpp>
#include <opm/parser/eclipse/Parser/ParserRecord.hpp>
#include <opm/parser/eclipse/Parser/ParserIntItem.hpp>
#include <opm/parser/eclipse/Parser/ParserEnums.hpp>

using namespace Opm;


ParserPtr createBPRParser() {
    ParserKWPtr parserKW(new ParserKW("BPR"));
    {
        ParserRecordPtr bprRecord(new ParserRecord());
        bprRecord->addItem(ParserIntItemConstPtr(new ParserIntItem("I", SINGLE)));
        bprRecord->addItem(ParserIntItemConstPtr(new ParserIntItem("J", SINGLE)));
        bprRecord->addItem(ParserIntItemConstPtr(new ParserIntItem("K", SINGLE)));
        
        parserKW->setRecord(bprRecord);
    }

    ParserPtr parser(new Parser());
    return parser;
}


BOOST_AUTO_TEST_CASE(parse_fileWithBPRKeyword_deckReturned) {
    boost::filesystem::path singleKeywordFile("testdata/integration_tests/bpr.data");
    ParserPtr parser = createBPRParser();

    BOOST_CHECK_NO_THROW( DeckPtr deck = parser->parse(singleKeywordFile.string()));
}


BOOST_AUTO_TEST_CASE(parse_fileWithBPRKeyword_DeckhasBRP) {
    boost::filesystem::path singleKeywordFile("testdata/integration_tests/bpr.data");
    ParserPtr parser = createBPRParser();

    DeckPtr deck = parser->parse(singleKeywordFile.string());
    BOOST_CHECK_EQUAL( true , deck.hasKeyword("BPR"));
}

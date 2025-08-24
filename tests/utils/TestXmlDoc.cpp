/****************************************************************************//*
 *  Copyright (C) 2025 Marek M. Cel
 *
 *  This file is part of MC-Mass.
 *
 *  MC-Mass is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MC-Mass is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 ******************************************************************************/

#include <gtest/gtest.h>

#include <utils/XmlDoc.h>

#define TEMP_XML_FILE "temp.xml"

class TestXmlDoc : public ::testing::Test
{
protected:
    TestXmlDoc() {}
    virtual ~TestXmlDoc() {}
    void SetUp() override {}
    void TearDown() override
    {
        // remove temporary file temp.xml
        std::remove(TEMP_XML_FILE);
    }
};


TEST_F(TestXmlDoc, CanConstruct)
{
    XmlDoc* doc = nullptr;
    EXPECT_NO_THROW(doc = new XmlDoc());
    delete doc;
}


TEST_F(TestXmlDoc, CanDestruct)
{
    XmlDoc* doc = new XmlDoc();
    EXPECT_NO_THROW(delete doc);
}


TEST_F(TestXmlDoc, CanInstantiate)
{
    XmlDoc doc;
}


TEST_F(TestXmlDoc, CanInstantiateAndOpenFile)
{
    XmlDoc doc("../tests/utils/data/test_xml_sample_data.xml");
    EXPECT_TRUE(doc.isOpen());
}


TEST_F(TestXmlDoc, CanCreateRootNode)
{
    XmlDoc doc;

    XmlNode rootNode = doc.createRootNode("test_root");
    EXPECT_TRUE(rootNode.isValid());
    EXPECT_STREQ(rootNode.getName().c_str(), "test_root");
}


TEST_F(TestXmlDoc, CanGetRootNode)
{
    XmlDoc doc("../tests/utils/data/test_xml_sample_data.xml");
    EXPECT_TRUE(doc.isOpen());

    XmlNode rootNode = doc.getRootNode();
    EXPECT_TRUE(rootNode.isValid());
    EXPECT_STREQ(rootNode.getName().c_str(), "test_root");
}


TEST_F(TestXmlDoc, CanGetPath)
{
    XmlDoc doc("../tests/utils/data/test_xml_sample_data.xml");
    EXPECT_TRUE(doc.isOpen());

    std::string file = doc.getPath().string();
    EXPECT_STREQ(file.c_str(), "../tests/utils/data/test_xml_sample_data.xml");
}


TEST_F(TestXmlDoc, CanOpenFile)
{
    XmlDoc doc;
    EXPECT_NO_THROW(doc.openFile("../tests/utils/data/test_xml_sample_data.xml"));
    EXPECT_TRUE(doc.isOpen());
}


TEST_F(TestXmlDoc, CanOpenFileEmpty)
{
    XmlDoc doc;
    EXPECT_NO_THROW(doc.openFile("../tests/utils/data/test_xml_sample_data_empty.xml"));
    EXPECT_FALSE(doc.isOpen());
}


TEST_F(TestXmlDoc, CanOpenFileNotExisting)
{
    XmlDoc doc;

    EXPECT_NO_THROW(doc.openFile("../tests/utils/data/test_xml_sample_data_not_existing.xml"));
    EXPECT_FALSE(doc.isOpen());
}


TEST_F(TestXmlDoc, CanCloseFile)
{
    XmlDoc doc("../tests/utils/data/test_xml_sample_data.xml");
    EXPECT_TRUE(doc.isOpen());
    EXPECT_NO_THROW(doc.closeFile());
    EXPECT_FALSE(doc.isOpen());
}


TEST_F(TestXmlDoc, CanSaveFile)
{
    XmlDoc doc;

    XmlNode rootNode = doc.createRootNode("test_root");
    XmlNode childNode = rootNode.addChildElement("test_child");
    XmlNode textNode = childNode.addText("lorem ipsum");

    EXPECT_TRUE(Result::Success == childNode.addAttribute("test_attr", "test_value"));

    EXPECT_TRUE(rootNode.isValid());
    EXPECT_STREQ(rootNode.getName().c_str(), "test_root");

    EXPECT_TRUE(childNode.isValid());
    EXPECT_TRUE(childNode.isElement());
    EXPECT_STREQ(childNode.getName().c_str(), "test_child");

    EXPECT_TRUE(textNode.isValid());
    EXPECT_TRUE(textNode.isText());
    EXPECT_STREQ(textNode.getText().c_str(), "lorem ipsum");

    EXPECT_TRUE(Result::Success == doc.saveFile(TEMP_XML_FILE));
    EXPECT_TRUE(doc.isOpen());

    doc.closeFile();

    XmlDoc doc2(TEMP_XML_FILE);
    EXPECT_TRUE(doc2.isOpen());
    XmlNode rootNode2 = doc2.getRootNode();
    EXPECT_TRUE(rootNode2.isValid());
    EXPECT_STREQ(rootNode2.getName().c_str(), "test_root");
    XmlNode childNode2 = rootNode2.getFirstChildElement("test_child");
    XmlNode textNode2 = childNode2.getFirstChild();
    EXPECT_TRUE(childNode2.isValid());
    EXPECT_TRUE(childNode2.isElement());
    EXPECT_STREQ(childNode2.getName().c_str(), "test_child");
    EXPECT_TRUE(childNode2.hasAttribute("test_attr"));
    EXPECT_STREQ(childNode2.getAttribute("test_attr").c_str(), "test_value");
    EXPECT_TRUE(textNode2.isValid());
    EXPECT_TRUE(textNode2.isText());
    EXPECT_STREQ(textNode2.getText().c_str(), "lorem ipsum");
}


TEST_F(TestXmlDoc, CanSaveEmptyFile)
{
    XmlDoc doc;

    EXPECT_FALSE(Result::Success == doc.saveFile(TEMP_XML_FILE));
    EXPECT_FALSE(doc.isOpen());
    doc.closeFile();

    XmlDoc doc2(TEMP_XML_FILE);
    EXPECT_FALSE(doc2.isOpen());
}

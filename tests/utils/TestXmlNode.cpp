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

#include <utils/XmlNode.h>
#include <utils/XmlDoc.h>


class TestXmlNode : public ::testing::Test
{
protected:
    TestXmlNode() {}
    virtual ~TestXmlNode() {}
    void SetUp() override {}
    void TearDown() override {}
};


TEST_F(TestXmlNode, CanConstruct)
{
    XmlNode *node = nullptr;
    EXPECT_NO_THROW(node = new XmlNode());
    delete node;
}


TEST_F(TestXmlNode, CanDestruct)
{
    XmlNode *node = new XmlNode();
    EXPECT_NO_THROW(delete node);
}


TEST_F(TestXmlNode, CanInstantiate)
{
    XmlNode node;
}


TEST_F(TestXmlNode, CanInstantiateAndCopy)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";
    std::shared_ptr<std::filesystem::path> path_sp = std::make_shared<std::filesystem::path>(path);

    xmlDocPtr  doc  = xmlParseFile(path.c_str());
    xmlNodePtr root = xmlDocGetRootElement(doc);

    XmlNode node0(root, path_sp);

    XmlNode node(node0);

    EXPECT_STREQ(node.getPath().string().c_str(), path.c_str());

    xmlFreeDoc(doc);
}


TEST_F(TestXmlNode, CanInstantiateAndMove)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";
    std::shared_ptr<std::filesystem::path> path_sp = std::make_shared<std::filesystem::path>(path);

    xmlDocPtr  doc  = xmlParseFile(path.c_str());
    xmlNodePtr root = xmlDocGetRootElement(doc);

    XmlNode node0(root, path_sp);
    XmlNode node(std::move(node0));

    EXPECT_STREQ( node.getPath().string().c_str(), path.c_str() );

    xmlFreeDoc(doc);
}


TEST_F(TestXmlNode, CanInstantiateFromNodeAndFile)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";
    std::shared_ptr<std::filesystem::path> path_sp = std::make_shared<std::filesystem::path>(path);

    xmlDocPtr  doc  = xmlParseFile(path.c_str());
    xmlNodePtr root = xmlDocGetRootElement(doc);

    XmlNode node(root, path_sp);

    EXPECT_STREQ(node.getPath().string().c_str(), path.c_str());

    xmlFreeDoc(doc);
}


TEST_F(TestXmlNode, CanAddChildElement)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";
    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    XmlNode child = root.addChildElement("child");

    EXPECT_TRUE(child.isValid());
    EXPECT_TRUE(child.isElement());
    EXPECT_STREQ("child", child.getName().c_str());

    XmlNode child1 = root.getFirstChildElement("child");
    EXPECT_TRUE(child1.isValid());
    EXPECT_TRUE(child1.isElement());
}


TEST_F(TestXmlNode, CanAddText)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";
    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    XmlNode child = root.addChildElement("child");
    XmlNode text = child.addText("test");
    EXPECT_TRUE(text.isValid());
    EXPECT_TRUE(text.isText());
    EXPECT_STREQ("test", text.getText().c_str());
}


TEST_F(TestXmlNode, CanAddAttribute)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_EQ(Result::Success, root.addAttribute("attribute_c", "C"));

    EXPECT_STREQ("C", root.getAttribute("attribute_c").c_str());
}


TEST_F(TestXmlNode, CanGetAttribute)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_STREQ("A" , root.getAttribute("attribute_a").c_str());
    EXPECT_STREQ("B" , root.getAttribute("attribute_b").c_str());
    EXPECT_STREQ(""  , root.getAttribute("attribute_x").c_str());
}


TEST_F(TestXmlNode, CanSetAttribute)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_EQ(Result::Success, root.setAttribute("attribute_a", "AA"));
    EXPECT_EQ(Result::Success, root.setAttribute("attribute_b", "BB"));

    EXPECT_STREQ("AA", root.getAttribute("attribute_a").c_str());
    EXPECT_STREQ("BB", root.getAttribute("attribute_b").c_str());
}


TEST_F(TestXmlNode, CanGetAttributes)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    XmlNode::Attributes attributes = root.getAttributes();

    EXPECT_EQ( 2, attributes.size() );

    XmlNode::Attributes::iterator it_a = attributes.find("attribute_a");
    XmlNode::Attributes::iterator it_b = attributes.find("attribute_b");

    EXPECT_NE(attributes.end(), it_a);
    EXPECT_NE(attributes.end(), it_a);

    EXPECT_STREQ("A" , it_a->second.c_str());
    EXPECT_STREQ("B" , it_b->second.c_str());
}


TEST_F(TestXmlNode, CanGetFirstChild)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    XmlNode child = root.getFirstChild();

    EXPECT_TRUE(child.isValid());
    EXPECT_TRUE(child.isText());
    EXPECT_STREQ("\nLorem ipsum\n", child.getText().c_str());
}


TEST_F(TestXmlNode, CanGetFirstChildElement)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    XmlNode child = root.getFirstChildElement();

    EXPECT_TRUE(child.isValid());
    EXPECT_TRUE(child.isElement());
    EXPECT_STREQ("sibling_1", child.getName().c_str());
}


TEST_F(TestXmlNode, CanGetFirstChildElementByName)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    XmlNode child = root.getFirstChildElement("sibling_2");

    EXPECT_TRUE(child.isValid());
    EXPECT_TRUE(child.isElement());
    EXPECT_STREQ("sibling_2", child.getName().c_str());
}


TEST_F(TestXmlNode, CanGetFirstChildElementNoChildren)
{
    std::string path = "../tests/utils/data/test_xml_sample_data_no_children.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    XmlNode child = root.getFirstChildElement();

    EXPECT_FALSE(child.isValid());
}


TEST_F(TestXmlNode, CanGetFile)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_STREQ(path.c_str(), root.getPath().string().c_str());

    XmlNode child = root.getFirstChildElement();

    EXPECT_STREQ(path.c_str(), child.getPath().string().c_str());
}


TEST_F(TestXmlNode, CanGetFileAndLine)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_STREQ((path + "(2)").c_str(), root.getPathAndLine().c_str());

    XmlNode child = root.getFirstChildElement();

    EXPECT_STREQ((path + "(4)").c_str(), child.getPathAndLine().c_str());
}


TEST_F(TestXmlNode, CanGetLine)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_EQ(2, root.getLine());

    XmlNode child = root.getFirstChildElement();

    EXPECT_EQ(4, child.getLine());

    XmlNode invalid;
    EXPECT_EQ(std::numeric_limits<int>::quiet_NaN(), invalid.getLine());
}


TEST_F(TestXmlNode, CanGetName)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_STREQ("test_root", root.getName().c_str());

    XmlNode child = root.getFirstChildElement();

    EXPECT_STREQ("sibling_1", child.getName().c_str());

    XmlNode invalid;
    EXPECT_STREQ("", invalid.getName().c_str());
}


TEST_F(TestXmlNode, CanGetNextSibling)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_STREQ("test_root", root.getName().c_str());

    XmlNode child1 = root.getFirstChildElement();
    XmlNode child2 = child1.getNextSibling();

    EXPECT_TRUE(child2.isValid());
    EXPECT_TRUE(child2.isText());
    EXPECT_STREQ("\ndolor sit amet\n", child2.getText().c_str());

    XmlNode child3 = child2.getNextSibling();
    EXPECT_TRUE(child3.isValid());
    EXPECT_TRUE(child3.isElement());

    XmlNode child4 = child3.getNextSibling();
    EXPECT_TRUE(child4.isValid());
    EXPECT_TRUE(child4.isText());
    EXPECT_STREQ("\n", child4.getText().c_str());

    XmlNode child5 = child4.getNextSibling();
    EXPECT_TRUE(child5.isValid());
    EXPECT_TRUE(child5.isComment());

    XmlNode child6 = child5.getNextSibling();
    EXPECT_TRUE(child6.isValid());
    EXPECT_TRUE(child6.isText());
    EXPECT_STREQ("\n", child6.getText().c_str());

    XmlNode child7 = child6.getNextSibling();
    EXPECT_FALSE(child7.isValid());
}


TEST_F(TestXmlNode, CanGetNextSiblingElement)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_STREQ( "test_root", root.getName().c_str() );

    XmlNode child1 = root.getFirstChildElement();

    XmlNode child2 = child1.getNextSiblingElement();
    EXPECT_TRUE(child2.isValid());
    EXPECT_TRUE(child2.isElement());
    EXPECT_STREQ("sibling_2", child2.getName().c_str());

    XmlNode child3 = child2.getNextSiblingElement();
    EXPECT_FALSE(child3.isValid());
}


TEST_F(TestXmlNode, CanGetText)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    XmlNode child = root.getFirstChild();
    EXPECT_TRUE(child.isValid());
    EXPECT_TRUE(child.isText());
    EXPECT_STREQ("\nLorem ipsum\n", child.getText().c_str());

    XmlNode child1 = root.getFirstChildElement();
    EXPECT_STREQ("", child1.getText().c_str());

    XmlNode child2 = child1.getNextSibling();
    EXPECT_TRUE(child2.isValid());
    EXPECT_TRUE(child2.isText());
    EXPECT_STREQ("\ndolor sit amet\n", child2.getText().c_str());
}


TEST_F(TestXmlNode, CanSetText)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    XmlNode child = root.getFirstChild();
    EXPECT_TRUE(child.isValid());
    EXPECT_TRUE(child.isText());

    EXPECT_EQ(Result::Success, child.setText("test"));

    EXPECT_STREQ("test", child.getText().c_str());
}


TEST_F(TestXmlNode, CanCheckIfNodeHasAttribute)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_TRUE(root.hasAttribute("attribute_a"));
    EXPECT_TRUE(root.hasAttribute("attribute_b"));

    EXPECT_FALSE(root.hasAttribute("attribute_x"));
}


TEST_F(TestXmlNode, CanCheckIfNodeHasAnyAttributes)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_TRUE(root.hasAttributes());

    XmlNode child = root.getFirstChildElement();

    EXPECT_FALSE(child.hasAttributes());

    XmlNode inavlid;
    EXPECT_FALSE(inavlid.hasAttributes());
}


TEST_F(TestXmlNode, CanCheckIfNodeHasAnyChildren)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_TRUE(root.hasChildren());

    XmlNode child = root.getFirstChildElement();
    EXPECT_FALSE(child.hasChildren());

    XmlNode inavlid;
    EXPECT_FALSE(inavlid.hasChildren());
}


TEST_F(TestXmlNode, CanCheckIfNodeIsAttribute)
{
    XmlNode inavlid;
    EXPECT_FALSE(inavlid.isAttribute());
}


TEST_F(TestXmlNode, CanCheckIfNodeIsComment)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_FALSE(root.isComment());

    XmlNode child1 = root.getFirstChildElement();
    EXPECT_FALSE(child1.isComment());

    XmlNode child2 = child1.getNextSibling();
    EXPECT_FALSE(child2.isComment());

    XmlNode child3 = child2.getNextSibling();
    EXPECT_FALSE(child3.isComment());

    XmlNode child4 = child3.getNextSibling();
    EXPECT_FALSE(child4.isComment());

    XmlNode child5 = child4.getNextSibling();
    EXPECT_TRUE(child5.isComment());

    XmlNode inavlid;
    EXPECT_FALSE(inavlid.isComment());
}


TEST_F(TestXmlNode, CanCheckIfNodeIsElement)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_TRUE(root.isElement());

    XmlNode child = root.getFirstChild();
    EXPECT_FALSE(child.isElement());

    XmlNode inavlid;
    EXPECT_FALSE(inavlid.isElement());
}


TEST_F(TestXmlNode, CanCheckIfNodeIsText)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_FALSE(root.isText());

    XmlNode child = root.getFirstChild();
    EXPECT_TRUE(child.isText());

    XmlNode inavlid;
    EXPECT_FALSE(inavlid.isText());
}


TEST_F(TestXmlNode, CanCheckIfNodeIsValid)
{
    std::string path = "../tests/utils/data/test_xml_sample_data.xml";

    XmlDoc doc(path.c_str());
    XmlNode root = doc.getRootNode();

    EXPECT_TRUE(root.isValid() );

    XmlNode child1 = root.getFirstChildElement();
    EXPECT_TRUE(child1.isValid());

    XmlNode child2 = child1.getNextSibling();
    EXPECT_TRUE(child2.isValid());

    XmlNode child3 = child2.getNextSibling();
    EXPECT_TRUE(child3.isValid());

    XmlNode child4 = child3.getNextSibling();
    EXPECT_TRUE(child4.isValid());

    XmlNode child5 = child4.getNextSibling();
    EXPECT_TRUE(child5.isValid());

    XmlNode child6 = child5.getNextSibling();
    EXPECT_TRUE(child6.isValid());

    XmlNode child7 = child6.getNextSibling();
    EXPECT_FALSE(child7.isValid());
}


TEST_F(TestXmlNode, CanAssign)
{
    XmlNode node;

    std::string path = "../tests/utils/data/test_xml_sample_data.xml";
    std::shared_ptr<std::filesystem::path> path_sp = std::make_shared<std::filesystem::path>(path);

    xmlDocPtr  doc  = xmlParseFile(path.c_str());
    xmlNodePtr root = xmlDocGetRootElement(doc);

    XmlNode node0(root, path_sp);

    node = node0;

    EXPECT_STREQ(node.getPath().string().c_str(), path.c_str());

    xmlFreeDoc(doc);
}


TEST_F(TestXmlNode, CanAssignMove)
{
    XmlNode node;

    std::string path = "../tests/utils/data/test_xml_sample_data.xml";
    std::shared_ptr<std::filesystem::path> path_sp = std::make_shared<std::filesystem::path>(path);

    xmlDocPtr  doc  = xmlParseFile(path.c_str());
    xmlNodePtr root = xmlDocGetRootElement(doc);

    XmlNode node0(root, path_sp);
    node = std::move(node0);

    EXPECT_STREQ(node.getPath().string().c_str(), path.c_str());

    xmlFreeDoc(doc);
}

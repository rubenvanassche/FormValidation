/*
 * FormTest.cpp
 *
 *  Created on: 18 mei 2013
 *      Author: Ruben
 */
#include "FormTest.h"

void FormTest(){
	FA::Test t("Form");
	FA::Form f("TestForm");

	// Loading
	t.expectFalse(f.addComponents("ComponentsDoesNotExist.txt"));
	t.expectTrue(f.addComponents("components.txt"));

	t.equal(f.getData().size(),0);

	t.expectFalse(f.load("FormDoesNotExist.txt"));
	t.expectTrue(f.load("form.txt"));

	t.equal(f.getData().size(),6);

	t.expectTrue(f.add("Works", "Email"));
	t.expectFalse(f.add("Works not", "EmailDoesNotExist"));

	t.equal(f.getData().size(),7);

	t.equal(f.getData()["Works"],"");

}

void ComponentTest(){
	FA::Test t("Component");

	FA::Component c("Regex");
	t.expectTrue(c.regex("a+b+c+dee"));
	t.expectTrue(c.process("aee"));
	t.expectFalse(c.process("ae"));

	FA::Component e("DB");
	t.expectFalse(e.db("nonexisting.txt"));
	t.expectTrue(e.db("DB/citys.txt"));
	t.expectTrue(e.process("Antwerpen"));
	t.expectFalse(e.process("antwerpen"));
	t.expectFalse(e.process("bestaatniet"));

	FA::Component f("DB with corrector");
	t.expectFalse(f.db("nonexisting.txt", true));
	t.expectTrue(f.db("DB/citys.txt", true));
	t.expectTrue(f.process("Antwerpen"));
	t.expectTrue(f.process("antwerpen"));
	t.expectFalse(e.process("bestaatniet"));

	//t.equal("eeea", f.DBcorrector("éèëa"));
	t.equal("antwerpen", f.DBcorrector("Antwerpen"));
	t.equal("zuidafrika", f.DBcorrector("Zuid-Afrika"));
	t.equal("dansendansendansen", f.DBcorrector("Dansen Dansen Dansen"));
}

void FieldTest(){
	FA::Test t("Field");

	FA::Component e("DB");
	e.db("DB/citys.txt");

	FA::Field f(&e, "City");
	t.expectFalse(f.isRequired());
	f.required();
	t.expectTrue(f.isRequired());
	f.notRequired();
	t.expectFalse(f.isRequired());

	t.equal(f.makeLabel(), "- City\n");
	f.length(20);
	t.equal(f.getLength(), 20);
	t.equal(f.makeLabel(), "- City (minimum-lengte: 20)\n");
	f.required();
	t.equal(f.makeLabel(), "- City (minimum-lengte: 20) *\n");

	t.equal(f.getValue(), "");
	t.expectFalse(f.isFilledIn());

	t.expectFalse(f.check("Nietbestaandestad"));
	t.expectFalse(f.isFilledIn());
	t.expectTrue(f.check("Langemark-Poelkapelle"));
	t.expectFalse(f.isFilledIn());

	t.expectFalse(f.process("Nietbestaandestad"));
	t.expectFalse(f.isFilledIn());
	t.expectTrue(f.process("Langemark-Poelkapelle"));
	t.expectTrue(f.isFilledIn());
	t.equal(f.getValue(), "Langemark-Poelkapelle");


	FA::Field g(&e, "City");

	g.length(9);
	t.expectFalse(g.check("Boom"));
	t.expectTrue(g.check("Antwerpen"));

	g.length(0);
	t.expectTrue(g.check("Boom"));
	t.expectTrue(g.check("Antwerpen"));

	g.length(9);
	t.expectFalse(g.process("Boom"));
	t.expectTrue(g.process("Antwerpen"));

	FA::Field h(&e, "City");

	t.expectFalse(h.isRequired());
	t.expectTrue(h.check(""));
	t.expectTrue(h.check("Boom"));
	t.expectFalse(h.check("Nietbestaandestad"));

	h.required();
	t.expectTrue(h.isRequired());
	t.expectFalse(h.check(""));
	t.expectTrue(h.check("Boom"));
	t.expectFalse(h.check("Nietbestaandestad"));

	FA::Field i(&e, "City");
	t.expectTrue(i.process("Antwerpen"));
	t.expectTrue(i.isAccepted());
	t.expectFalse(i.check("Boom"));
	t.expectTrue(i.process("Boom"));
	t.equal(i.getValue(), "Antwerpen");
}


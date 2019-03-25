const assert = require('chai').assert;
const htmlStatement = require('../src').htmlStatement;
const plays = require('./plays.json');
const invoices = require('./invoices.json');

const expected = `<h1>Statement for BigCo</h1>
<table>
<tr><th>play</th><th>seats</th><th>cost</th></tr>
 <tr><td>Hamlet</td><td>55</td><td>$650.00</td></tr>
 <tr><td>As You Like It</td><td>35</td><td>$580.00</td></tr>
 <tr><td>Othello</td><td>40</td><td>$500.00</td></tr>
</table>
<p>Amount owed is <em>$1,730.00</em></p>
<p>You earned <em>47</em> credits</p>
`;

describe('HtmlStatement', () => {
    describe('#htmlStatement()', () => {
        it('html text', function () {
            assert.equal(htmlStatement(invoices[0], plays), expected);
        });
    });
});
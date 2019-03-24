const assert = require('chai').assert;
const statement = require('../src');
const plays = require('./plays.json');
const invoices = require('./invoices.json');

const expected = `Statement for BigCo
  Hamlet: $650.00 (55 seats)
  As You Like It: $580.00 (35 seats)
  Othello: $500.00 (40 seats)
Amount owned is $1,730.00
You earned 47 credits
`;

describe('Statement', () => {
    describe('#statement()', () => {
        it('plait text result', function () {
            assert.equal(statement(invoices[0], plays), expected);
        });
    });
});
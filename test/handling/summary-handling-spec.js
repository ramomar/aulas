const assert = require('chai').assert;
const moment = require('moment');

const scheduleJson    = require('../schedule.json');
const Schedule        = require('mobile/schedule/schedule.js')(scheduleJson);
const SummaryHandling = require('mobile/handling/summary-handling.js');

describe('SummaryHandling#handleSummaryRequest', function test() {
  it('should yield a correct SESSION_TIME summary', function() {
    const time     = moment('8:40', ['HH:mm']);
    const handling = SummaryHandling(Schedule, makeTestClient(), time, 1);

    const expected = 'SESSION_TIME|0/3|50|VISIO|4204|SISINT|4206';
    const actual   = handling.handleSummaryRequest();

    assert.equal(expected, actual);
  });

  it('should yield a correct BREAK_TIME summary', function test() {
    const time = moment('9:30', ['HH:mm']);
    const handling = SummaryHandling(Schedule, makeTestClient(), time, 1);

    const expected = 'BREAK_TIME|1/3|200|SISINT|4206';
    const actual   = handling.handleSummaryRequest();

    assert.equal(expected, actual);
  });

  it('should yield a correct FREE_TIME summary', function test() {
    const time = moment('23:30', ['HH:mm']);
    const handling = SummaryHandling(Schedule, makeTestClient(), time, 1);

    const expected = 'FREE_TIME';
    const actual   = handling.handleSummaryRequest();

    assert.equal(expected, actual);
  })
});

function makeTestClient() {
  return {
    sendSummary: (summary) => summary
  };
}

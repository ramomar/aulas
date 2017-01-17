const assert = require('chai').assert;
const moment = require('moment');

const scheduleJson    = require('../schedule.json');
const Schedule        = require('mobile/schedule/schedule.js')(scheduleJson);
const SummaryHandling = require('mobile/handling/summary-handling.js');

describe('SummaryHandling#handleSummaryRequest', function test() {
  it('should yield a correct SESSION_TIME summary', function() {
    const timeA     = moment('8:40', ['HH:mm']);
    const handlingA = SummaryHandling(Schedule, testClient, timeA, 1);
    const expectedA = 'SESSION_TIME|0/3|50|VISIO|4204|SISINT|4206';
    const actualA   = handlingA.handleSummaryRequest();

    const timeB     = moment('17:20', ['HH:mm']);
    const handlingB = SummaryHandling(Schedule, testClient, timeB, 1);
    const expectedB = 'SESSION_TIME|2/3|30|VERISOFT|4203|GO_HOME_TIME';
    const actualB   = handlingB.handleSummaryRequest();

    assert.equal(expectedA, actualA);
    assert.equal(expectedB, actualB);
  });

  it('should yield a correct BREAK_TIME summary', function test() {
    const time     = moment('9:30', ['HH:mm']);
    const handling = SummaryHandling(Schedule, testClient, time, 1);

    const expected = 'BREAK_TIME|1/3|200|SISINT|4206';
    const actual   = handling.handleSummaryRequest();

    assert.equal(expected, actual);
  });

  it('should yield a correct GO_HOME_TIME summary', function test() {
    const time     = moment('23:30', ['HH:mm']);
    const handling = SummaryHandling(Schedule, testClient, time, 1);

    const expected = 'GO_HOME_TIME';
    const actual   = handling.handleSummaryRequest();

    assert.equal(expected, actual);
  });

  it('should yiled a correct FREE_TIME summary', function test() {
    const time     = moment('11:20', ['HH:mm']);
    const handling = SummaryHandling(Schedule, testClient, time, 6);

    const expected = 'FREE_TIME';
    const actual   = handling.handleSummaryRequest();

    assert(expected, actual);
  });
});

const testClient = {
  sendSummary: (summary) => summary
};

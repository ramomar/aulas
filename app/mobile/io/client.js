function sendSummary(summary, ackCallback, nackCallback) {
  Pebble.sendAppMessage({Summary: summary}, ackCallback, nackCallback);
}

function sendMobileReady(ackCallback) {
  Pebble.sendAppMessage({MobileReady: 1}, ackCallback);
}

module.exports = {
  sendSummary,
  sendMobileReady
};

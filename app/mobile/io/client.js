function sendMessage(message, ackCallback, nackCallback) {
  Pebble.sendAppMessage(message, () => {
    console.info(`Successfully sent ${JSON.stringify(message)}`);
    ackCallback();
  }, (e) => {
    console.error(`Message ${JSON.stringify(message)} failed: `
      + JSON.stringify(e));
    nackCallback(e);
  });
}

function sendSummary(summary, ackCallback, nackCallback) {
  sendMessage({Summary: summary}, ackCallback, nackCallback);
}

function sendMobileReady(ackCallback, nackCallback) {
  sendMessage({MobileReady: 1}, ackCallback, nackCallback);
}

module.exports = {
  sendSummary,
  sendMobileReady
};

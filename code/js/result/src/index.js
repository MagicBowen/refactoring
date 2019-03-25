const createStatementData = require("./createStatementData");
const TextFormatter = require("./formatter").TextFormatter;
const HtmlFormatter = require("./formatter").HtmlFormatter;

function render(data, formatter) {
    formatter.onTitle(data.customer);
    formatter.onPerformancesBegin();
    for (let perf of data.performances) {
        formatter.onPerformance(perf.play.name, perf.audience, usd(perf.amount));
    }
    formatter.onPerformancesEnd();
    formatter.onSummary(usd(data.totalAmount), data.totalVolumeCredits);
    return formatter.result;
}

function usd(aNumber) {
    return new Intl.NumberFormat("en-US", {
        style: "currency", currency: "USD", minimumFractionDigits: 2}).format(aNumber/100);
}

module.exports.statement = function (invoice, plays) {
    return render(createStatementData(plays, invoice), new TextFormatter());
}

module.exports.htmlStatement = function (invoice, plays) {
    return render(createStatementData(plays, invoice), new HtmlFormatter());
}

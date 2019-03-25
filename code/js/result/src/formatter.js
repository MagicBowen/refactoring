class TextFormatter {
    constructor() {
        this._result = "";
    }

    get result(){
        return this._result;
    }

    onTitle(customer) {
        this._result += `Statement for ${customer}\n`;
    }

    onPerformance(playName, audience, usdAmount) {
        this._result += `  ${playName}: ${usdAmount} (${audience} seats)\n`;
    }

    onSummary(usdTotalAmount, totalVolumeCredits) {
        this._result += `Amount owned is ${usdTotalAmount}\n`;
        this._result += `You earned ${totalVolumeCredits} credits\n`;        
    }

    onPerformancesBegin() {}
    onPerformancesEnd() {}
}

class HtmlFormatter {
    constructor() {
        this._result = "";
    }

    get result(){
        return this._result;
    }

    onTitle(customer) {
        this._result += `<h1>Statement for ${customer}</h1>\n`;
    }

    onPerformance(playName, audience, usdAmount) {
        this._result += ` <tr><td>${playName}</td><td>${audience}</td>`;
        this._result += `<td>${usdAmount}</td></tr>\n`;
    }

    onSummary(usdTotalAmount, totalVolumeCredits) {
        this._result += `<p>Amount owed is <em>${usdTotalAmount}</em></p>\n`;
        this._result += `<p>You earned <em>${totalVolumeCredits}</em> credits</p>\n`;       
    }

    onPerformancesBegin() {
        this._result += "<table>\n";
        this._result += "<tr><th>play</th><th>seats</th><th>cost</th></tr>\n";
    }
    onPerformancesEnd() {
        this._result += "</table>\n";
    }
}

module.exports.TextFormatter = TextFormatter;
module.exports.HtmlFormatter = HtmlFormatter;

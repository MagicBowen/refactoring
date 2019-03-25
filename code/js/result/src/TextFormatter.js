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

module.exports = TextFormatter;

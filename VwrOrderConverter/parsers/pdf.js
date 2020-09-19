var PDFParser = require("pdf2json");

function processPdf(text, pdfBuffer)
{
  if (text.substr(0, 4) != "%PDF")
    return Promise.reject();
  return new Promise((resolve, reject) =>
  {
    let pdfParser = new PDFParser();
    pdfParser.on("pdfParser_dataError", reject);
    pdfParser.on("pdfParser_dataReady", resolve);
    pdfParser.parseBuffer(pdfBuffer);
  });
}


module.exports = {parse:processPdf, id:"pdf"};
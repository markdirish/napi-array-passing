const addon = require('./build/Release/addon.node');

addon.passArray(["abc", 123], (error1, printer) => {
  if (error1) {
    throw error1;
  }

  printer.printArray((error2, array) => {
    if (error2) {
      throw error2;
    }

    console.log(array);
  });
});
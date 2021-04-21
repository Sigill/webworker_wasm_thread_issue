importScripts('./test.js');

self.onmessage = function (evt) {
  if (evt.data.action === "expansive_function") {
    var r = Module.expansive_function();
    self.postMessage(`Expansive function returned ${r}.`);
  }

  if (evt.data.action === "parallel_sum_expansive_functions") {
    var r = Module.parallel_sum_expansive_functions();
    self.postMessage(`Parallel expansive function returned ${r}.`);
  }
}
const BLYNK_TOKEN = 'Tic_nyd0OmtLl2oqXewLNa_xhpny19GV'; // Replace with your Blynk project token

function fetchBlynkData(pin, callback) {
  const url = `https://blynk.cloud/external/api/get?token=Tic_nyd0OmtLl2oqXewLNa_xhpny19GV&pin=${pin}`;

  fetch(url)
    .then(response => response.text())
    .then(data => callback(data))
    .catch(error => console.error('Error fetching data from Blynk:', error));
}

function getBpm() {
  fetchBlynkData('V0', data => {
    document.getElementById('bpm-value').textContent = `${data} BPM`;
    checkAlerts('BPM', parseFloat(data));
  });
}

function getTemperature() {
  fetchBlynkData('V1', data => {
    document.getElementById('temperature-value').textContent = `${data} °C`;
    checkAlerts('Temperature', parseFloat(data));
  });
}

function getSpO2() {
  fetchBlynkData('V2', data => {
    document.getElementById('spo2-value').textContent = `${data} %`;
    checkAlerts('SpO2', parseFloat(data));
  });
}

function addReminder() {
  const reminderText = document.getElementById('new-reminder').value;
  if (reminderText) {
    const ul = document.getElementById('medications-list');
    const li = document.createElement('li');
    li.appendChild(document.createTextNode(reminderText));
    ul.appendChild(li);
    document.getElementById('new-reminder').value = '';
  }
}

function checkAlerts(parameter, value) {
  const alertMessage = document.getElementById('alert-message');
  const medicationsList = document.getElementById('medications-list');
  let alert = '';

  medicationsList.innerHTML = ''; // Clear previous medications

  if (parameter === 'BPM' && value > 100) {
    alert = 'BPM is too high. You may need medication!';
    addMedication('Metoprolol (Lopressor, Toprol-XL)');
    addMedication('Atenolol (Tenormin)');
  } else if (parameter === 'Temperature' && value > 37.5) {
    alert = 'Temperature is too high. You may need medication!';
    addMedication('Acetaminophen');
    addMedication('Ibuprofen (Advil, Motrin IB)');
    addMedication('Aspirin');
  } else if (parameter === 'SpO2' && value < 92) {
    alert = 'SpO2 is too low. You may need medication!';
    addMedication('Acetazolamide');
  }

  if (alert) {
    alertMessage.textContent = alert;
    alertMessage.style.color = '#cc0000';
    alertMessage.style.fontWeight = 'bold';
  } else {
    alertMessage.textContent = 'No alerts';
    alertMessage.style.color = '';
    alertMessage.style.fontWeight = '';
  }
}

document.addEventListener('DOMContentLoaded', (event) => {
  getBpm();
  getTemperature();
  getSpO2();

  setInterval(getBpm, 10000); // Fetch BPM every 10 seconds
  setInterval(getTemperature, 10000); // Fetch Temperature every 10 seconds
  setInterval(getSpO2, 10000); // Fetch SpO2 every 10 seconds
});

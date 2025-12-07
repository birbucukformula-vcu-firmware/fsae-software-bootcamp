# 🏎️ Görev 2: İleri Seviye Gaz Pedalı Algoritması (ADC & Safety)

## 🎯 Amaç: Gerçek Dünya Verisiyle Çalışmak

Bu görevde bir Gömülü Yazılımcı gibi davranacak; ham veriyi işleyecek, voltaj sınırlarını denetleyecek ve güvenli sürüşü sağlayacaksınız.

---

## ⚙️ Senaryo: Ham Veriden Torka

Elinizde **12-bit ADC** (Analog-to-Digital Converter) okuyan bir sistem var.
* **Min Değer (0V):** 0
* **Max Değer (3.3V):** 4095

Ancak sensörlerimiz fiziksel olarak pedalın en altına ve en üstüne değmez.
* **Sensör 1 Çalışma Aralığı:** 1000 (0% Gaz) - 4000 (100% Gaz)
* **Sensör 2 Çalışma Aralığı:** 500 (0% Gaz) - 2500 (100% Gaz) *(Not: İkinci sensör farklı aralıkta çalışır!)*

### Kurallar Zinciri (Pipeline)

Kodunuz sırasıyla şu 3 aşamadan geçmelidir:

#### 1. Sınır Kontrolü (Out of Range Check - T11.8.8)
Sensörler fiziksel sınırlarının dışına çıkarsa (Kablo koptu veya Kısa devre oldu), sistem anında **HATA** vermelidir.
* Eğer Sensör 1 < 1000 veya > 4000 ise -> **HATA**
* Eğer Sensör 2 < 500 veya > 2500 ise -> **HATA**

#### 2. Mapping (Veri Dönüştürme)
Ham ADC verisini 0-100 arasına lineer oranlamanız (Linear Mapping) gerekir.
* Matematiksel Formül: $y = (x - in\_min) * (out\_max - out\_min) / (in\_max - in\_min) + out\_min$
* *İpucu:* Bunu bir fonksiyon haline getirip her iki sensör için de kullanın.

#### 3. Tutarlılık Kontrolü (Plausibility Check - T11.8.9)
Dönüştürülmüş yüzdeler (%) arasındaki fark **%10'dan büyükse** -> **HATA**

---

## 🛠️ Teknik Gereksinimler

### 1. Struct Yapısı
Veriler global değişkenlerde değil, bir yapı içinde taşınmalıdır.
```c
typedef struct {
    int raw_adc_1;      // Ham ADC verisi (Kullanıcı girecek)
    int raw_adc_2;      // Ham ADC verisi (Kullanıcı girecek)
    int percent_1;      // Hesaplanmış %
    int percent_2;      // Hesaplanmış %
    int final_torque;   // Motora giden tork
    char status[20];    // "OK", "OutOfRange", "Implausible"
} PedalState;

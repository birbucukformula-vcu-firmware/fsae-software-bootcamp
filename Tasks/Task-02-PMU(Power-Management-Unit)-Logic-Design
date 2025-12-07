🏎️ Görev 2: Akıllı Start-Stop Sistemi (Engine Control Logic)
🎯 Amaç ve Senaryo
Modern yarış araçlarında ve Formula Student arabalarında motor, basit bir anahtarla açılmaz. Güvenlik gereği, sürücünün aracı çalıştırma niyetini doğrulayan bir mantık (Logic) silsilesi vardır.

Bu görevde, aracın Güç Yönetim Birimi (Power Management Unit) yazılımını simüle edeceksiniz. Amacımız, sürücünün Fren Pedalı ve Start Butonu ile yaptığı kombinasyonlara göre aracın güç modlarını değiştiren güvenli bir Durum Makinesi (State Machine) tasarlamaktır.

⚙️ Sistemin Çalışma Mantığı (Algoritma)
Sisteminizde 3 ana güç modu bulunmalıdır:

KAPALI (OFF): Sistemin enerjisi kesik, sadece işlemci uyanık.

AKSESUAR (ACC): Motor kapalı, ancak gösterge paneli ve telemetri açık.

ÇALIŞIYOR (RUN): Motor aktif, yüksek gerilim hattı açık, araç sürüşe hazır.

Geçiş Kuralları (Transition Rules): Sistemin bir durumdan diğerine geçmesi için şu kurallara kesinlikle uyması gerekir:

Senaryo 1 (Teyp Modu): Sistem KAPALI iken, sürücü Frene Basmadan butona basarsa -> Sistem AKSESUAR moduna geçer.

Senaryo 2 (Motor Başlatma): Sistem KAPALI veya AKSESUAR modundayken, sürücü Frene Basarak butona basarsa -> Sistem ÇALIŞIYOR moduna geçer.

Senaryo 3 (Kapatma): Sistem AKSESUAR modundayken, sürücü Frene Basmadan butona tekrar basarsa -> Sistem KAPALI moduna döner.

Senaryo 4 (Motor Durdurma): Sistem ÇALIŞIYOR modundayken, sürücü butona basarsa (Fren durumu önemsiz) -> Sistem direkt KAPALI moduna döner.

🛠️ Teknik Gereksinimler (Constraints)
Kodunuz aşağıdaki teknik şartları sağlamak zorundadır:

Veri Yapıları:

Durumları (OFF, ACC, RUN) yönetmek için mutlaka typedef enum kullanın. Asla 0, 1, 2 gibi "sihirli sayılar" kullanmayın.

Aracın tüm verilerini (Anlık Mod, Fren Durumu, Voltaj vb.) tek bir çatı altında toplamak için typedef struct kullanın.

Akış Kontrolü:

Durum geçişlerini yönetmek için switch-case yapısı kullanın.

İç içe geçmiş if-else bloklarından (Spagetti Kod) kaçının.

Simülasyon:

Program sonsuz bir döngüde çalışmalı ve kullanıcıdan klavye komutları beklemelidir:

[F]: Fren pedalına bas/çek (Toggle).

[B]: Start butonuna bas.

[Q]: Çıkış.

🧹 Clean Code & Mühendislik Standartları (Çok Önemli!)
Bu görevde kodun çalışması kadar, nasıl yazıldığı da puanlanacaktır. Takımımızda "Kirli Kod" kabul edilmez. Aşağıdaki kurallara uymayan kodlar (Pull Request'ler) reddedilecektir.

1. İsimlendirme (Naming Convention)
Değişken ve fonksiyon isimleri yaptığı işi anlatmalıdır.

❌ Yanlış: int a;, int durum;, void islem(); (Bu 'a' nedir? Hangi işlem?)

✅ Doğru: int fren_pedali_durumu;, GuctModu anlik_mod;, void motoru_baslat();

Kural: Değişkenler için snake_case (küçük harf, alt çizgi), Enum ve Sabitler için UPPER_CASE kullanın.

2. Fonksiyonel Ayrıştırma (Modularity)
Tüm kodu main() fonksiyonunun içine yığmayın. main fonksiyonu sadece bir yönetici olmalıdır. İşleri taşeronlara (yardımcı fonksiyonlara) dağıtın.

❌ Yanlış: Durum kontrolü, ekran yazdırma, veri okuma hepsi main içinde.

✅ Doğru:

void durumu_ekrana_yazdir(AracVerisi *veri);

void girisleri_oku(AracVerisi *veri);

void durum_degistir(AracVerisi *veri);

3. Yorum Satırları (Documentation)
Yorum satırı, kodun "Ne" yaptığını değil, "Neden" yaptığını anlatmalıdır.

❌ Gereksiz: i++; // i'yi bir artır. (Bunu zaten görüyoruz).

✅ Faydalı: // FSAE T11.8 Kurali: Motorun baslamasi icin fren basili olmak zorundadir.

4. Sihirli Sayılardan Kaçınma (No Magic Numbers)
Kodun içinde anlamı bilinmeyen sayılar olmamalıdır.

❌ Yanlış: if (sicaklik > 100) ... (100 ne? Kaynama noktası mı? Limit mi?)

✅ Doğru:

#define MAX_MOTOR_SICAKLIK 100

if (sicaklik > MAX_MOTOR_SICAKLIK) ...

📤 Teslim Kuralları (Git Workflow)
Dosya Adı: Task02_StartStop_Ad_Soyad.c

Branch: Kendi Fork'unuzda feature/start-stop-logic adında bir dal açarak çalışın.

Test Kanıtı: Kodunuzun çalıştığını gösteren terminal çıktısını (Screenshot) README.md dosyasına veya PR açıklamasına ekleyin.

Pull Request: "Clean Code" kurallarına uyduğunuzdan emin olduktan sonra ana repoya PR açın.

/*
 * Strawberry Music Player
 * Copyright 2018, Jonas Kvinge <jonas@jkvinge.net>
 *
 * Strawberry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Strawberry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Strawberry.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef AUDIOSCROBBLER_H
#define AUDIOSCROBBLER_H

#include "config.h"

#include <memory>

#include <QtGlobal>
#include <QObject>
#include <QString>

#include "scrobblerservices.h"

class Application;
class Song;
class NetworkAccessManager;
class ScrobblerService;

class AudioScrobbler : public QObject {
  Q_OBJECT

 public:
  explicit AudioScrobbler(Application *app, QObject *parent = nullptr);
  ~AudioScrobbler();

  void ReloadSettings();

  bool IsEnabled() const { return enabled_; }
  bool IsOffline() const { return offline_; }
  bool ScrobbleButton() const { return scrobble_button_; }
  int SubmitDelay() const { return submit_delay_; }

  void UpdateNowPlaying(const Song &song);
  void Scrobble(const Song &song, const int scrobble_point);
  void Love(const Song &song);
  void ShowConfig();
  void ConnectError();

  ScrobblerService *ServiceByName(const QString &name) const { return scrobbler_services_->ServiceByName(name); }

  template <typename T>
  T *Service() {
    return static_cast<T*>(this->ServiceByName(T::kName));
  }

 public slots:
  void ToggleScrobbling();
  void ToggleOffline();
  void Submit();
  void WriteCache();
  void ErrorReceived(QString);

 signals:
  void ErrorMessage(QString);
  void ScrobblingEnabledChanged(bool value);
  void ScrobblingOfflineChanged(bool value);
  void ScrobbleButtonVisibilityChanged(bool value);

 private:

  Application *app_;
  ScrobblerServices *scrobbler_services_;

  bool enabled_;
  bool offline_;
  bool scrobble_button_;
  int submit_delay_;

};

#endif  // AUDIOSCROBBLER_H